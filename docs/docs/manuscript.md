<H1>A low-cost framework to control behavioral experiments using an Arduino, Python, and a web browser</H1>


# Abstract

Controlling an experiment with an Arduino microcontroller has become commonplace in scientific labs. A major bottle-neck in making these experiments main-stream is the difficulty in their use. Once embedded into an experiment, the control of an Arduino often involves detailed command line interaction which detracts from potentially complicated experiments. Here, we present a web interface to control an experiment with an Arduino. In particular, we have built a motorized treadmill to be used for behavioral experiments during awake head-fixed in vivo two-photon imaging. We provide schematics for building the treadmill and electronics as well as Arduino and Python code to control the experiment from within a web browser. This system also includes synchronized video recording. This is a general-purpose open-source framework where Arduino based experiments can be controlled through a web interface. The source-code can be easily modified to meet new and unique experimental designs.

# Introduction

Behavioral experiments performed in parallel to in vivo imaging and electrophysiological recording have become common.

They multi-model experiments are fundamental to understanding the bi-directional relationship between behavior and brain activity.

For example: spherical treadmill (ref, ref), licking experiments (ref, ref), hippocampal place fields (ref, ref).

Commercially available laboratory equipment is available either as individual pieces of hardware or pre-packaged systems.

give two example systems: master-8 (ref), treadmill (ref).

Yet these commercial systems are limited in a number of ways. They are designed to do one thing and, given their proprietary design, are hard to extend to new experimental configurations. These systems are also expensive, and are thus difficult to obtain with limited funding for a potentially underfunded or exploratory experiment. Given their cost, it is also difficult to scale the use of these commercial systems beyond having a single system in a given laboratory.

Here we present an inexpensive open-source system to control a behavioral experiment with an Arduino using a simple web browser interface. This system is low-cost and easy to build, can be adapted to new experimental configurations, and can be replicated into multiple systems running in parallel.

## System design

### Hardware

The hardware for the system includes an Arduino microcontroller, a stepper motor and motor driver, a rotary encoder, a host computer, and a circular treadmill. 

We provide a GitHub repository and website with documentation for building the hardware and wiring the components ([1](#fn1)).

### Software

The core of the software is C++ code run on an Arduino microcontroller. This controls a trial based experiment where each trial has a pre-duration followed by a number of pulses with each pulse moving the treadmill at a given rate for a given duration.

We provide the full source-code with documentation in a Github repository ([1](#fn1)).

## Using the system

### Arduino interface

### Python interface

### Web browser interface

## Applications

### In vivo vascular dynamics

### In vivo Ca++ imaging

## Discussion

In our research we need to simultaneously measure an animals behavior while performing two-photon imaging. While there are off the shelf solutions to this, we saw a need for a well documented and flexible open-source solution.

By providing this solution we hope to lower the barrier-to-entry for others who need to do similar behavioral experiments.

We have made the system extendible by providing multiple programming interfaces including a sub-set of C++ on an Arduino, a Python environment that can run an experiment, and a simple to use web-browser interface.

## Conflict of Interest Statement

The authors declare that they have no commercial or financial affiliations in the subject matter or materials discussed in this manuscript.


## Acknowledgments

## Footnotes

<a name="fn1"></a>1: [http://cudmore.github.com/treadmill][1]

[1]: http://cudmore.github.com/treadmill

## References
