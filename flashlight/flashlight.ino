/*
Flashlight scetch 

x = done 
o = todo 
mode01-normal: 
  sub_modes: 
    x 1.1 - low light 
    x 1.2 - medium light 
    x 1.3 - maximum light 
mode02-broken: 
  sub_modes:
    x 2.1 - permanent flickering 
    x 2.2 - permanent flickering with lights out pauses
    x 2.3 - occasional flickering 
    x 2.4 - occasional flickering with lights out pauses
mode03-blink: 
  sub_modes: 
    x 3.1 - sos 
    x 3.2 - on, off 
    x 3.3 - pulse 
    x 3.4 - strob with frequenzy changes 
mode04-RGB+W:
  sub_modes:
    o 4.1 - white 
    o 4.2 - red 
    o 4.3 - green 
    o 4.4 - blue 
    o 4.5 - yellow 
    o 4.6 - cyan
    o 4.7 - magenta 

Allman style
*/

const int led_pin_11 = 11; 

int off = 0;
int low = 25;
int medium = 100;
int high = 255;

void sos_blink(int off, int high)
{
  for (int i = 1; i <= 3; i++) 
  {
    analogWrite(led_pin_11, high);
    delay(500);
    analogWrite(led_pin_11, off);
    delay(500);
  }
  for (int i = 1; i <= 3; i++) {
    analogWrite(led_pin_11, high);
    delay(1000);
    analogWrite(led_pin_11, off);
    delay(500);
  }
  for (int i = 1; i <= 3; i++) 
  {
    analogWrite(led_pin_11, high);
    delay(500);
    analogWrite(led_pin_11, off);
    delay(500);
  }
  delay(1500);
}

void led_pulse(int led_pin, float time_step, int pause) {
  // time step should be between 0.0099 - 0.0025
  // pause between 1 - 5
  for(float t = 0; t < 2*PI; t += time_step) {
    float value = (cos(t - PI)*0.5+0.5)*255; 
    analogWrite(led_pin, value); 
    delay(pause);   
  }   
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() 
{
  int mode = 3;      // change by pressing button for 5 seconds
  int sub_mode = 3;  // change by shortly pressing button
  if (mode > 4) { mode = 1; }

  if (mode == 1)  // normal flashlight mode 
  {
    if (sub_mode > 3) { sub_mode = 1; }
    if (sub_mode == 1)  // low mode 
    {
      analogWrite(led_pin_11, low);
    }
    else if (sub_mode == 2)  // medium mode 
    {
      analogWrite(led_pin_11, medium);
    }
    else if (sub_mode == 3)  // high mode 
    {
      analogWrite(led_pin_11, high);
    }
  }
  else if (mode == 2)  // effect modes 
  {
    if (sub_mode > 4) { sub_mode = 1; }
    if (sub_mode == 1) 
    {
      int flicker_delay_time = (random(50, 3000) / 5); 
      int light_intensity = random(155, 255);  
      analogWrite(led_pin_11, light_intensity);
      delay(flicker_delay_time);
    }
    else if (sub_mode == 2)
    {
      int flicker_delay_time = (random(50, 3000) / 5); 
      int light_intensity = random(155, 255);  
      analogWrite(led_pin_11, light_intensity);
      delay(flicker_delay_time);
      int blackout = random(1, 20);
      if (blackout == 1)
      {
        analogWrite(led_pin_11, 0);
        delay(flicker_delay_time / 2);
      }
    }
    else if (sub_mode == 3)
    {
      int no_flicker_delay_time = (random(10, 30)) * 1000; 
      analogWrite(led_pin_11, high);
      delay(no_flicker_delay_time);

      while (1)
      {
        int flicker_delay_time = (random(50, 3000) / 5); 
        int light_intensity = random(155, 255);  
        analogWrite(led_pin_11, light_intensity);
        delay(flicker_delay_time);
        int break_chance = random(1, 100);
        if (break_chance == 1 || break_chance == 10) { break; }

      }
    }
    else if (sub_mode == 4)
    {
      int no_flicker_delay_time = (random(10, 30)) * 1000; 
      analogWrite(led_pin_11, high);
      delay(no_flicker_delay_time);

      while (1)
      {
        int flicker_delay_time = (random(50, 3000) / 5); 
        int light_intensity = random(155, 255); 
        int break_chance = random(1, 100);
        int blackout = random(1, 20);
        analogWrite(led_pin_11, light_intensity);
        delay(flicker_delay_time);
        if (blackout == 1)
        {
          analogWrite(led_pin_11, 0);
          delay(flicker_delay_time / 2);
        }
        if (break_chance == 1 || break_chance == 10) { break; }
      }
    }
  }
  else if (mode == 3)  // blink and pulse modes 
  {
    if (sub_mode > 4) { sub_mode = 1; }
    if (sub_mode == 1)
    {
      sos_blink(off, high);
    }
    else if (sub_mode == 2)
    {
      analogWrite(led_pin_11, high);
      delay(500);
      analogWrite(led_pin_11, off);
      delay(500);
    }
    else if (sub_mode == 3)
    {
      // pulse 
      led_pulse(led_pin_11, 0.0099, 5); 
    }
    else if (sub_mode == 4)
    {
      // strob 
      for (int i = 1; i < 40; i++)
      {
        analogWrite(led_pin_11, high);
        delay(45);
        analogWrite(led_pin_11, off);
        delay(45);
      }
      for (int i = 1; i < 20; i++)
      {
        analogWrite(led_pin_11, high);
        delay(75);
        analogWrite(led_pin_11, off);
        delay(75);
      }
    }
  }
  else if (mode == 4)  // RGB+W
  {
    // test
    analogWrite(led_pin_11, low);
    delay(3000);
    analogWrite(led_pin_11, medium);
    delay(3000);
    analogWrite(led_pin_11, high);
    delay(3000);

  }


}