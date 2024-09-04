# DwarfFortress
## Screenshot
![PlayixFortress_Screenshot](https://github.com/user-attachments/assets/7294f107-6dd1-4fb9-9f0f-d359a7c1a73e)
## Windows build of the game
Link
## 3rd party packages
* Boost 1.86 (Signal)
* nlohmann/json
# Code design & decisions
This section describes the most important elements used in implementing the game.

## MVC
As stated in the requirement, game follows MVC principles. Each view (map, player stats, player inventory, player actions) has a corresponding model that will trigger view update. Controller manipulates models via domain classes that contain logic for each domain.

## Domains and models
In order to avoid a direct manipulation of models by a controller, domain were created that manipulate their corrensponding models. Each domain can contain one or more unique pointers to a model that they will manipulate. Controller uses domains to manipulate models indiretcly (via commands for player input and enemies movement, combat state machine during combat, etc.)

### World domain
World domain handles the map, specifically map initialization, getting entities and removing them on the map, moving entities and signaling that world model has been updated (positions on the map).
### Entity domains
Entity domains are: base entity, player, enemy, chest. Each domain is responsible for all basic functionalities that those entities require and also for signaling the view that something has been updated (player domain only for stats and inventory).
### Inventory domain
Inventory domains include item logic, actual inventory logic, and item usage logic (more on that below). Inventory domain signals the view when change in inventory happens.
### IO domain
This domain is reponsible for saving and loading the game from the save file.

## Signals
In order to follow MVC guidelines, Boost's signals were used to notify the views that their model has changed. Each view has a callback method (with model pointer as a parameter) that will be used to update the view. Signal are also used to notify the controller that something has happened, so their usage is not limited to views.

## Views
Game has one main view and four subviews, one for each model (map, stats, inventory, actions). Main view has references to all subviews, and cached out buffers of them all. The idea is to update only the subview who's model has beed modified. To achieve this, when model is modified the signal is sent by the responsible domain and output buffer of that subview is updated. Then the whole view is rendered, by taking cached output buffers and the updated one to form the main view. This being a console app imposed some limitation, in terms that whole console text needs to be updated, but still, only one subview is updated at a time. Also, to avoid flickering when writting to console, some workarounds were implemented (like moving the cursor to the top-left, and adding empty spaces where shorter text replaces longer text).

### Main View
Holds references to all subviews and uses their out buffers to render the whole view.
### MapSubView
Uses WorldDataModel to create a map output for rendering.
### StatsSubView
Uses EntityStatsDataModel to create a player stats output for rendering.
### InventorySubView
Uses InventoryDataModel to create a player inventory output for rendering.
### InventorySubView
Uses PlayerActionsDataModel to create a player actions output for rendering.
Player actions include two main pieces of information: game state (movement phase and combat phase) and last player's action (damage dealt, damage taken, picked up item, etc.).
It's a cosmetic feature that improves quality of life since player can see what's happening during each game state.

## Player input
Player input uses commands to keep everything clean, and to leave an option for undo/redo functionality (not in requirements). Input manager lives inside the main controller, and based on player input executes commands that in turn use domains to manipulate the models.

## Inventory & item usage
Inventory contains the standard methods for storing, droping and using items. Item usage (drinking potions and equipping weapons and armor) is done via chain of responsibility. Item handler service contains the list of all item handlers, and when player uses the item (whether consumable or equipable), item is passed through the chain by the item handler service. Each item handler tries to handle the item, and passes the item to its successor if it's not the right handler. Adds a layer of abstraction to the solution.

## Combat state machine
A simple state machine was created to handle the combat phase. It checks for combat start (when player and enemy overlap on the map), initiates combat, alternates between player and enemy turns (with resolve turn state in between to check for health) and ends the combat. Since it can happen that two enemies are on the same map tile, stata machine will start another combat phase when the previous one is finished. Enemies are removed from the world when defeated and they drop an item from their inventory.

## Saving & loading
A service was created for this purpose. It serializes all necessary entities on the map, and the map as well.
