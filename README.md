# Hybrid-Exoskeleton-Glove

**Title:** An Open-Source, Hybrid Exoskeleton Glove Equipped with Variable Stiffness Joints, Abduction Capabilities, and a Telescopic Extra Thumb

**Description:** 
<p align="justify"> Robotic hand exoskeletons have become a popular and efficient technological solution for assisting people that suffer from neurological conditions and for enhancing the capabilities of healthy individuals. This class of devices ranges from rigid and complex structures to soft, lightweight, wearable gloves. Despite the progress in the field, most existing devices do not provide the same dexterity as the healthy human hand. In this work, we propose a hybrid (tendon-driven and pneumatic), lightweight, affordable, easy-to-operate exoskeleton glove equipped with variable stiffness, laminar jamming structures, abduction/adduction capabilities, and a pneumatic telescopic extra thumb that increases grasp stability. </p>  

<p align="justify"> The soft, robotic exoskeleton glove was designed to assist human hands with limited mobility during the motion rehabilitation process and to improve the grasping and dexterous manipulation capabilities of the hand, in both impaired and able-bodied individuals. The proposed device is composed of two main systems: the soft exoskeleton glove and the control unit. The control unit is composed of five Dynamixel XM430-W350-T motors, two mini 12V air pumps, one 12V vacuum pump, three solenoid valves, a microcontroller (Robotis OpenCM9.04), and a small circuit to control the air pumps. All six tendons are connected to the pulleys of the motors and run though polyurethane tubes that are used for tendon routing from the control unit to the soft glove. The ring and pinky fingers have a supplementary role during object grasping \cite{liarokapis2013quantifying}, therefore, they are connected to the same motor. A vacuum tube connects the vacuum pump to the jamming structures located at the back of the hand, and another two tubes connect the air pumps to the abduction soft actuators and the inflatable, telescopic thumb.  </p> 

<p align="justify"> The soft glove system of the proposed device is composed of a thin, high sensibility glove, a tendon-driven system that consists of six artificial tendons, a pneumatic system that consists of four soft actuators, and five laminar jamming structures. Five plastic tendon termination structures are stitched onto the fingertips of the glove. Soft anchor points have been added in the glove structure for rerouting the tendon, offering better sensibility of the grasped objects than the rigid anchor points. The tendon-driven system has a tendon connected to each of the fingertip structures and an extra tendon that is connected to the thumb's interphalangeal joint region so as to allow for the execution of the thumb's opposition motion. A tendon-driven solution for the thumb abduction / opposition was chosen over a soft actuator based solution, in order to avoid the obstruction of the region between the index and the thumb, as many different grasps types require the object to be positioned in-between the thumb and the index metacarpophalangeal joints (in the human hand purlicue area). The tendons used in the exoskeleton glove are made out of a low friction braided fiber of high-performance UHMWPE (Ultra-High Molecular Weight Polyethylene) and can withstand forces up to 500 N. The soft actuators are used for two different purposes, to allow for the execution of the abduction / adduction motion of the fingers and to increase grasp stability by activating a telescopic extra thumb that provides grasp support. Three pneumatic chambers have been developed with a "V" shape, and they have been fixed in the region in between the fingers to facilitate the execution of the abduction motion of the fingers. The soft actuator was designed to provide active assistance on finger abduction and passive on finger adduction, once the human hand is naturally adducted.  </p> 

<p align="justify"> The soft actuators that have been designed are described in the following subsections. At the back of each digit, laminar jamming structures are attached to control the force required to close the digits, to maintain the fingers steady in a desired configuration, and to perform passive extension of the fingers keeping the hand in its natural, zero effort position. The laminar jamming structures can achieve multiple stiffnesses by applying a pressure gradient into the system and relying on the friction between the layers. A single vacuum pump is used to jam the layers of all fingers, enabling variable joint stiffness. A flex sensor was placed at the index finger region and is used to trigger a desired function of the exoskeleton glove when a set bending angle is achieved.  </p> 

<p align="justify"> The operation of the device is straightforward. Using the smartphone app, the user selects the mode desired to control the exoskeleton glove. The user can combine the motions (e.g., full grasp with abducted fingers or tripod grasp with the extra thumb inflated and the jamming structures activated). The flex sensor can be selected to trigger the desired motion when a set bending angle is reached. The information is transmitted to a microcontroller through Bluetooth communication. Then, the microcontroller activates the chosen actuators that are connected to the glove. Each air supply is connected to a solenoid valve that is used to release the air pressure of the system when the glove returns to its original position. The entire system is powered by a 12V power supply. A battery can be added to the control unit to make the device portable and wearable. The amount of force applied by each finger is determined through a current control of each motor and can be adjusted according to the user's needs. </p>  

<p align="center"><img src="https://github.com/newdexterity/Hybrid-Exoskeleton-Glove/blob/master/Exoskeleton_Glove_Figures/main2.png" width="50%"></img></p>

