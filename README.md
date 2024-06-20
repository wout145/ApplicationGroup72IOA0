
# ArDuinoHD

This application is a web-based visual programming editor for Arduino. It is tailored towards children with ADHD between the ages of 10 and 12 and it is based on the existing [BlocklyDuino](https://github.com/BlocklyDuino/BlocklyDuino).
For our web-based interface we have focused on young students diagnosed with Attention Deficit Hyperactivity Disorder (ADHD). To help them learn programming in this block-based environment, we have constructed a reward system, since frequent positive reinforcement has been shown to improve the motivation and performance of young students with ADHD. In addition, we have implemented an embedded instruction functionality. Breaking down a program into steps can reduce the cognitive load for children with ADHD.

### Features

* Reward System

The reward system is implemented through a timer that can be accessed in the bar of buttons on the top of the screen. It contains a "Start Timer" button, a "Stop Session" button and a "Clear Highscore" button. The "Start Timer" button starts a timer. The duration of the timer is 3 minutes, to ensure frequent rewards. The timer will count down to 0, after which a popup will appear, which one has to click to obtain points. However, this popup will only appear if the user has interacted with the blocks in the mean time. This promotes useful interaction with the interface. When the popup is clicked, the timer will automatically continue. When the user is done, they should click "Stop Session". Which will save their score as the highscore if it is higher than the current highscore. This highscore will be saved across sessions. If the user wants to reset their highscore to 0, they click the "Clear Highscore" button. See image below for the bar of buttons with the score counters.

![Button Bar](https://i.ibb.co/JFNmVmG/image-2024-06-20-093840211.png "Button Bar")

* Instructions

The embedded instructions functionality can be enabled by clicking the "Need help?" shown in the image above. When clicked, the instructions pop-up will appear as shown in the left side of the picture below. The right side of the picture below shows an example the instructions for one of the concepts. All the instructions consist out of one image (top) and one GIF (bottom) for easy to understand visual explanation. 

![Instructions Popup](https://i.ibb.co/s5FQcPY/image.png "Instructions Pop-Up")



* Use Cases

Two use cases have been implemented to show off our interface. Specialized blocks for these use cases can be found in the "Memory Game 1" and "Memory Game 2" tabs in the side bar on the left. As the name suggest, these use cases are memory games one can play with a simple arduino setup. This setup is an Arduino UNO with 4 LEDs, 4 pushbuttons and an LCD screen. When wired in the same way as suggested by the code produced by our specialized blocks, you can experiment with these use cases yourself. To implement any of the two use cases with the interface, simply drag all the blocks of a memory game into the canvas and connect them. The order does not matter. Examples for both memory games are shown in the picture below.

![Memory Games](https://i.ibb.co/X56LSqN/image.png "Memory Games")

The first memory games goes as follows. The LEDs will light up in a random sequence of the length you provided in the blocks. After this sequence has ended, you have to press the buttons in the same sequence as the LEDs lit up. Subsequently, the LEDs will play a feedback sequence indicating wether your answer was correct or wrong.

In the second memory game, you must press the buttons to create your own sequence. This sequence should be of the length you provided in the blocks. After this, the LEDs will play a sequence. When this sequence has finished, you should press the left or right button, corresponding to wether the sequence the LEDs played was the same, or different from the one you entered. Lastly, the LEDs will play a feedback sequence indicating wether your answer was correct or wrong.

### How to install/use

* Download the project

If you haven't already, download the project code.

* Run the project

To start using the application, first make sure you have python version 2.7, Arduino IDE version 1.8.19 and xampp installed. If you haven't already, navigate to the xampp home directory, then to the htdocs folder and put the project files in here. Then, open a terminal and navigate to the project home directory called "Application Group 7 2IOA0". Here, run the "arduino_web_server.py" file with python2.7. If you are using windows, do this by typing `python ./arduino_web_server.py`. A message similar to the one in the following picture should appear:

![Button Bar](https://i.ibb.co/VVg5tQG/Screenshot-2024-05-24-093650.png "Button Bar")

Now you can open the provided link in your preferred browser and you are ready to use the product.

If no code appears in the Arduino tab, try opening the interface in a different browser.
If there are any errors or things that are unclear, please navigate to the [BlocklyDuino GitHub Page](https://github.com/BlocklyDuino/BlocklyDuino) for more information.