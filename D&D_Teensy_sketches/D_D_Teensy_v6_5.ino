//odd behaviour - disrt crunch which leans towards spitting hiss wrinkles
//3x SINE waves - none audible
//bitcrusher before filter on pink noise channel 4 - 
//all knobs adjust some noise / filter element

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine3;          //xy=53,158
AudioSynthWaveformSine   sine2;          //xy=54,111
AudioSynthWaveformSine   sine1;          //xy=66,60
AudioSynthNoisePink      pink1;          //xy=119,242
AudioFilterStateVariable filter1;        //xy=390,212
AudioMixer4              mixer1;         //xy=514,108
AudioOutputI2S           i2s1;           //xy=769,86
AudioConnection          patchCord1(sine3, 0, mixer1, 2);
AudioConnection          patchCord2(sine2, 0, mixer1, 1);
AudioConnection          patchCord3(sine1, 0, mixer1, 0);
AudioConnection          patchCord4(pink1, 0, filter1, 0);
AudioConnection          patchCord5(pink1, 0, filter1, 1);
AudioConnection          patchCord6(filter1, 0, mixer1, 3);
AudioConnection          patchCord7(mixer1, 0, i2s1, 0);
AudioConnection          patchCord8(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=492,322
// GUItool: end automatically generated code

// GUItool: end automatically generated code

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.7);
 
  sine1.amplitude(0.8);
  sine1.frequency(220);
  sine1.phase(90);
  
  sine2.amplitude(0.8);
  sine2.frequency(440);
  sine2.phase(95);

  sine3.amplitude(0.8);
  sine3.frequency(880);
  sine3.phase(100);

  pink1.amplitude(0.8);

  mixer1.gain(0, 0.7);
  mixer1.gain(1, 0.7);
  mixer1.gain(2, 0.7);
  mixer1.gain(3, 0.7);
  delay(100);

  filter1.frequency(9);
  filter1.resonance(9); 
  //Q ranges from 0.7 to 5.0. Resonance greater than 0.707 will amplify the signal near the corner frequency. 
  //You must attenuate the signal before input to this filter, to prevent clipping.

}

void loop() {
  // put your main code here, to run repeatedly:
  float knob_A0 = (float)analogRead(A0) / 1023;
  float knob_A1 = (float)analogRead(A1) / 1023;
  float knob_A2 = (float)analogRead(A2) / 1023;
  float knob_A3 = (float)analogRead(A3) / 1023;
  float knob_A4 = (float)analogRead(A4) / 1023;
  float knob_A5 = (float)analogRead(A5) / 1023;
  float knob_A6 = (float)analogRead(A6) / 1023;
  float knob_A7 = (float)analogRead(A7) / 1023;

  // use Knobs to adjust the waveform frequency
  sine1.frequency(knob_A0);
  sine2.frequency(knob_A1);
  sine3.frequency(knob_A2);
  filter1.frequency(knob_A3);
  
  // pink1.(knob_A3); - some DRAMA filter cutoff effect parameter
    // use Knobs to adjust the amount of waveform amplitude
  sine1.amplitude(knob_A4);
  sine2.amplitude(knob_A5);
  sine3.amplitude(knob_A6);
  pink1.amplitude(knob_A7);
  
  // read the knob and adjust the filter frequency DRAMA
  int knob = analogRead(A3);
  // quick and dirty equation for exp scale frequency adjust
  float freq =  expf((float)knob / 150.0) * 10.0 + 80.0;
  filter1.frequency(freq);
  Serial.print("frequency = ");
  Serial.println(freq);
  delay(100);
}
