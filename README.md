# CS300_DSA_Analysis_and_Design

What was the problem you were solving in the projects for this course?

  I was building a course planner that could take a CSV file and make sure it actually made sense, and then let me search and display the data in a useful way. The real problem wasn’t just reading the file, it was making sure things like prerequisites were valid and that I could quickly find or list courses without doing a ton of extra work every time. Basically, take raw data, make it trustworthy, and organize it so it’s actually usable.

How did you approach the problem? Consider why data structures are important to understand.

  I started by thinking through the logic in pseudocode so I didn’t just jump straight into coding blindly. The big decision was using a binary search tree instead of something simple like a vector. That mattered because the tree keeps everything sorted automatically and makes searching faster. If I had used a basic list, I would have been constantly sorting or scanning through everything. This project made it pretty clear that the data structure you pick basically controls how your whole program behaves and performs.

How did you overcome any roadblocks you encountered while going through the activities or project?

  Honestly, I didn’t run into any major blockers on this one. Most of the work went pretty smoothly because I took the time upfront to think through the structure in pseudocode before jumping into the implementation. That made the actual coding pretty straightforward. The only real friction points were minor things like making sure the data flowed correctly from parsing into the tree and double-checking that everything stayed consistent, but nothing that required a major redesign. If anything, the biggest takeaway here is that doing the planning first prevented the kinds of problems that usually slow things down later.

How has your work on this project expanded your approach to designing software and developing programs?

  This forced me to stop writing everything as one big block of code and actually think about structure. I started separating things like parsing, validation, and storage instead of mixing them together. Writing the pseudocode first also made a big difference, it kept me from getting lost halfway through. Going forward, I need to remember that planning the structure upfront saves time and frustration later.

How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

  I’m a lot more aware now of how important it is to keep things clean and modular. Breaking logic into smaller functions made everything easier to follow and debug. Naming things clearly and adding comments actually helped when I came back to the code later. I also set things up so changes wouldn’t require rewriting everything, like keeping the data structure separate from the rest of the logic. The main takeaway here is to write code like I’m going to come back to it later and not remember anything.
