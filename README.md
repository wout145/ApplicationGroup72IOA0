
# Application Group 7 2IOA0

This application is a web-based visual programming editor for Arduino. It is tailored towards people with ADHD and based on the existing [BlocklyDuino](https://github.com/BlocklyDuino/BlocklyDuino).
For our web-based interface we have focused on young students diagnosed with Attention-deficit hyperactivity disorder (ADHD). To help them learn programming in this block-based environment, we have constructed a reward system, since frequent positive reinforcement has been shown to improve the motivation and performance of young students with ADHD.

### Features

* Reward System

The reward system is implemented through a timer that can be accessed in the bar of buttons on the top of the screen. It contains a "Start Timer" button, a "Stop Session" button and a "Clear Highscore" button. The "Start Timer" button starts a timer. For testing purposes and since this application is still a prototype, the duration of the timer is 10 seconds. The timer will count down to 0, after which a popup will appear, which one has to click to obtain points. When the popup is clicked, the timer will automatically continue. When the user is done, they should click "Stop Session". Which will save their score as the highscore if it is higher than the current highscore. This highscore will be saved across sessions. If the user wants to reset their highscore to 0, they click the "Clear Highscore" button. See image below for the bar of buttons with the score counters.

![Button Bar](https://i.ibb.co/Ln4w52m/Screenshot-2024-05-24-092221.png "Button Bar")

* Instructions

The instructions have yet to be implemented. The "Help" button will be used in the future to guide the user to the instructions.

* Use Cases

Two use cases will be implemented in the future. They will take the form of memory games. To this account, the sidebar on the left also already contains a "Memory Games" section.

### How to install/use

* Download the project

If you haven't already, download the project code.

* Run the project

To start using the application, first make sure you have python version 2.7, Arduino IDE version 1.8.19 and xampp installed. If you haven't already, navigate to the xampp home directory, then to the htdocs folder and put the project files in here. Then, open a terminal and navigate to the project home directory called "Application Group 7 2IOA0". Here, run the "arduino_web_server.py" file with python2.7. If you are using windows, do this by typing `python ./arduino_web_server.py`. A message similar to the one in the following picture should appear:

![Button Bar](https://i.ibb.co/VVg5tQG/Screenshot-2024-05-24-093650.png "Button Bar")

Now you can open the provided link in your preferred browser and you are ready to use the product.

If there is any errors or things that are unclear, please navigate to the [BlocklyDuino GitHub Page](https://github.com/BlocklyDuino/BlocklyDuino) for more information.