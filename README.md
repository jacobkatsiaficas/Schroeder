# Schroeder
Extended implementation of a Schroeder Reverb module in the RackAFX format, developed by Will Pirkle.

# Lower Level Description
Uses the basic All-Pass Filter + parallel Comb Filter topology from Schroeder's research with some tweaks -- most notable diffusion,
input and output filtering, and a multitapped predelay line. 

The processing chain is as follows:

SIGNAL IN -> single-pole LPF with adjustable gain -> 3 APF's to diffuse input -> 4 parallel Comb Filters ->
single-pole LPF with adjustable gain -> 2 APF's to diffuse output -> SIGNAL OUT

Gain on the input diffusion APF's is set to 0.6, while gain on the output diffusion APF's is set to 0.5. These were tweaked 
to minimize the ringing inherent to this type of reverb.

Combe filter gain is set based on the desired RT60, following an equation from Will Pirkle's "Designing Audio Effect Plugins in C++."

This reverb plugin is not ideal, Schroeder's design (as you can clearly hear) was prone to ringing. The diffusion and ad

# Use and modification
To use or tweak these, download Rack AFX, and open the Schroeder.prj file. Create a new project with the Reverb classes box checked,
and be sure to include the Tapped Delay header in your main class.

Github would not accept the entire directory (5 files would not push properly) so I only included those I thought could easily be added to a project to keep this repo lightweight.

