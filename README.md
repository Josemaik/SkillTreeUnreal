# UI_UnrealEngine
 Skill tree builded in UE5 with UMG.

## Set-Up Project:
1. Generate project files from SkillTreeUnreal.uproject
2. Open SkillTreeUnreal.sln
3. Left click in SkillTreeUnreal and Set as startup Project.
4. Ctrl + F5 or Play to start execution
5. When Unreal is open then press Alt + P or Play Buttom to test the project.

## Activity memory
My first idea was to create a UUserWidget class called Skill. This contains member variables to represent the different elements of the interface such as a canvas panel, button, icon, etc..., the type of skill managed by an enum, its cost in points, its status (whether it is unlocked or not) and an array of skills that represent the previous skills required to unlock this one. Additionally, it contains methods to check whether the skill is unlocked or not when it is pressed, change its appearance when it is unlocked, set the icons and initialize its state in the constructor.

The second step is to create a UUserWidget class called SkillTree that contains the necessary elements to build the tree, such as skills and branches. This class manages a counter for the skill points it collects from the Character class.

The Character class is responsible for creating the widget and adding it to the viewport. An Input Action ( Key E ) has been added to show or hide the tree.

Finally, UUSerWidget class called Modal was also created, which has a text prompt asking the user if they're sure about their action. Each skill has an associated modal to display it before it's unlocked.

## Recommendations 🚨🚨
Play in Full Screen
