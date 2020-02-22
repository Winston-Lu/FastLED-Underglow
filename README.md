# FastLED-Underglow
An implementation of the FastLED library to add underglow to any object. I used WS2812 LED's, and the configuration of the LED's and number of LED's are configurable. 

## Lighting Brightness
One digital IO pin is set to brightness up, and another pin is set to brightness down. 

## Lighting Profiles
Currently, a few lighting profiles are included:

### Solid Green
As the name implies

### Solid White
As the name implies. The current draw on this is high as all red, green, and blue LED's are on. I toned the brightness down for this one as to not exceed the power capacity my battery bank can handle (5V 2A).

### Green and White gradient
Using FastLED's sine function, a gradent starting at the middle of the green gradient will transisition to white and back to green. In a loop, the edge (not corner) that is connected to the data line will be the green edge, and the opposite side will be the white edge. The effect starts at the ends and transisitions to white in the middle

### Rainbow Cycle
RGB LED setups are incomplete without some rainbow mode. This just cycles the rainbow clockwise around the object.

### Rainbow Slide
This allows for a slide animation where the rainbow gradient does down towards the opposite edge. Much like the gradient, this effect starts on the ends of the LED strip and makes its way towards the middle of the strip.

### Solid Rainbow
The entire LED strip is one solid color as it transisitons through the color of the rainbow
