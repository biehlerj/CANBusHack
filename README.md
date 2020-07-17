# CANBusHack

Since 1996 OBD-II standard CAN Buses have been mandatory on all cars and light trucks sold in the United States. This repository contains a work done related to hacking my 2001 Toyota Highlander to not only try and make it more modern, but also to understand how the electronics work in a car and what it takes to automate a car. This is a passion project and the README will be updated to reflect what features have been added and when they were added.

## So what is a CAN Bus

For the people who like me at the beginning of this project don't know what a CAN Bus is let's go over what a CAN Bus is and how it works.

CAN stands for Controller Area Network and was released in 1986. It allows for microcontrollers and devices to communicate with each other without a host computer. In cars CAN Buses control almost everything from locking and unlocking your car, the AC, starting the car, and much more. When talking about automotive automation and self driving cars most of what the engineers are working on relates to how CAN buses send and receive information.

## Why hack your car

I wanted to learn what goes into making a car "smart" and decided I wanted to try to make my car smart. I am interested in car automation since that is such an interesting issue and since driving a car is one of my favorite hobbies and being a software engineer I wanted to understand how all the electronic components in my car talk to each other. As cars become "smarter" understanding how the components of the car talk to each other becomes a more useful skill. Driverless cars have been approved to carry passengers in the state of California and all the work of making a car driverless starts with sending, receiving, and interpreting data to/from a CAN Bus.

## What did you learn

Working on low-level product/project is a very different beast from working on high level/web product/project, there is often times proprietary software/hardware, speciality software/hardware, and/or little to no documentation or old/outdated documentation. There is often a high learning curve for low level programming especially in the automotive industry, since programming in cars is a relatively new/specialized field. I learned the importance of researching a project before starting and making sure all the right tools are bought before the project is started.

## What features are you working on

I'm currently working on the following features:

- Locking and unlocking my car using my Texas Instruments TM4C123G LaunchPad Development Board
- Locking and unlocking my car remotely from a web app.
- Monitoring my car for issues and sending a text message and/or email to me with the problem.
- Turning on my car remotely
- Controlling my AC remotely

## Features that are completed

Currently there are no features completed. As features are finished I will update this section

## The car

![the_car](../photos/highlander.png)

## The stack

The technologies being used:

- Pop!_OS 18.04
- SocketCAN
- More to be added as I update the repo.

## About the Author

I have always been interested in embedded systems, IoT, and other low-level fields and wanted to learn what it takes to create an app or product in those fields, so after talking to my father, who is an engineer, and being inspired to pursue a career in the IoT space by a mentor I decided to do this for my final project.

You can find me on Twitter [@Biehlerj](https://twitter.com/Biehlerj), on [LinkedIn](https://www.linkedin.com/in/jacob-biehler-475573139/), on GitHub at [biehlerj](https://github.com/biehlerj), and of course on [GitLab](https://gitlab.com/biehlerj).

## Using my project

Feel free to use my code/advice on how to hack your car to hack your own car. I only ask if you use any of my code to please credit what code of mine you use. If you'd like to contribute to this project please fork this project and if you'd like to have your work added feel free to add a merge request and I'll your info to this README and get an AUTHORS file together.
