# DiplomskiProjekt
Graduation project made in Unreal Engine 4. The point of the project is to create actors that use Behavior Tree and EQS to execute tasks.

If you wish to test out the actors, they are all located in the NPC folder. The Guard requires both the actor and a pathpoint to follow, otherwise
the editor may crash.

I have created 3 different actors that use Behavior Tree and one actor that uses EQS:

# Guard
![GuardNPC](https://user-images.githubusercontent.com/83773058/160403136-dcf0aca0-7289-4843-be6a-8092acadd721.png)
The Guard actor patrols a predetermined path that is made out of points. When the Guard sees the player, the actor will abort patrolling 
and immediately chase try to hit the player. On losing sight of the player, the Guard will investigate player's last known location for a set amount of time
before returning to his patrol.

Note: this Behavior Tree was made with the help of the youtube channels:

https://www.youtube.com/c/RyanLaley

https://www.youtube.com/channel/UCnN2iiHapP1uzJq64wlg3Zw

# Medic
![MedicNPC](https://user-images.githubusercontent.com/83773058/160404620-e4deaaff-19b1-480e-88be-bd090c5a126a.png)
Medic constantly monitors the player's health and if the player is hurt the Medic will try to heal them. The Medic has a set power capacity that is depleted 
when healing is performed. When the power capacity is below a determined treshold, the Medic will move towards the nearest recharge station to recharge.

# Stalker
![StalkerNPC](https://user-images.githubusercontent.com/83773058/160405473-70f3da00-5b97-4702-a6b0-975dfa4fcc62.png)
Stalker is an actor that only moves when he is not rendered on the player's monitor (that is, when the player can't see the actor), otherwise it wil slowly follow
the player.

# Shy
![ShyNPC](https://user-images.githubusercontent.com/83773058/160406778-6072fe80-3e82-442e-87b1-9b16274d1458.png)
The Shy actor uses EQS to hide from the player. He will find a nearby spot that is out of the player's view and move there.
