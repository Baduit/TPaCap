# HitlumChronicles
A little card game in cpp 20 (I use concept more than I should, but it is for learning purpose).

# TODO before alpha:
- Implement the effects of all buffs
- Implement the scenarios and create one

# TODO:
- Improve the graphics
- Create a starting menu
- Create the interface to create deck
- Add build process in the readme
- Add way more unit test in the rule (Hand, Deck, Arena, Player, etc)
- Make a core to do the communication between the engine instead of a big main
- Conceptify the has_buff() method in Monster
- Refactor the CardManager
- Probably a lot of little refactoring
- Add new buffs
- Balance the game
- Create a logger which can have categaroy (debug, fight informations, events)
- Use this logger to remove my ugly cout
- Implement real exception system (not just throw randomly some std::runtime_error or re-throw exception from the json library)
- Multiplayer (PvP)