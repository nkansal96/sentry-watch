# Sentry Watch

Made with love by Nikhil Kansal, Helen Lee, Su Thaw, and Nathan Yang at LA Hacks 2017.

## Inspiration
We were really inspired by Justin’s closing speech, where he urged us to think beyond our own personal problems and build something that could benefit the people around us. One of the things that we are constantly reminded of by the media is the constant stream of daunting civil crime occurring close to our homes. We decided that as UCLA students and L.A. residents, we had the power to create something to make our community safer.

## What It Does
Sentry Watch. A highly configurable, ergonomic wearable that monitors your movements and analyzes them in real-time for signs of struggle or running away [from trouble]. If so, it uses the configuration provided in the companion app to notify your emergency contacts with your location, and optionally emergency services (such as the police).

It also features a discrete panic button that allows the same functionality, but without causing an assailant to react harshly.

## How We Built It
We used the Particle Internet Button, a small, portable micro controller that has LEDs, a 3-axis accelerometer, and network connectivity for the core of our project. We wrote a complex C++ program to analyze raw accelerometer data in real-time to determine whether the wearer is in any kind of trouble. We used dynamic programming to fit the data as closely as possible to optimal curves and calculate the rhythm, jitter, and jerkiness and approximate a running derivative. If it surpassed a calibrated threshold, a notification was sent to our server to contact the user’s emergency contact with their location.

Our backend (Node.js, Express.js) also served as an API to let a user configure their wearable through an iOS app. It also had another interface to receive events from the Particle Internet Cloud to receive “panic” (button-press) and struggle (automatically-detected) events from the Particle. Upon detecting these events, it will check them against the user’s settings and send an SMS (Twilio) to their emergency contacts (if desired). It also served a static front-end to introduce our product. The app is hosted with Heroku.

The iOS app (Swift, Cocoa) acts as an interface to configure the Sentry Watch, with several options (your name, your emergency contacts, and which safety features you would like to activate).

## Challenges We Ran Into
The Particle Internet button was surprisingly stubborn to connect to the internet. Sometimes it wouldn’t recognize, or it wouldn’t connect, or it would turn off the computer’s connection to the internet. We had also tested the dynamic programming portion of the code on our laptops which ran perfectly well using mock data. However, when we transferred the logic and flashed our program to the device, we ran into issues with respect to the limited capabilities of the micro controller.

## Accomplishments That We're Proud Of
We genuinely feel like we created a device that benefits everyone in our society. It works pretty well for a hackathon project and almost always accurately detects a “fight or flight”. We are also very proud that were able to optimize and reduce such a complex algorithm to be able to run on a tiny micro-controller. Finally, for all of us, this was our first hardware hack and it was really fun to actually make something physical and combine it with our software knowledge and desire to create something beneficial for society.

## What We've Learned
We learned a great deal about programming micro controllers and the limitations that are present in programming such a small device. We also learned a great deal about the power and potential of the Internet of Things — and just how we can use it to make such unique and important ideas come to life. For every team member, there was a part of this project that allowed them to dive into an area of development completely foreign to the one they were familiar with. This is, in our opinion, the true value of a hackathon.

## What's next?
* Use a more powerful IoT device to leverage the full capability of the algorithm we developed, and possibly use more data more frequently.
* Suppose multiple Sentry Watches per user, user login into a dashboard with information about crimes in the area and previous alerts that may have been sent.


## Built With:
Particle Internet Button, C++, HTML, CSS, Javascript, Node.js, Express.js, Twilio, Heroku, Sketch, Github
