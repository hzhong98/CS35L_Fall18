READ ME

The first thing we want to do is see what parts of the program
are easiest to parallelize, and eventually see that the easiest
way to get the most work done is simply split up the work in
the big loop from the main function.

We are already given number of threads as a parameter and so we
feed that into the create pthread function along with a single
argument that you are allowed to give your function. Since the
pthread create takes a function, you make one with that big loop
that you wanted to parallelize.

Although there are some dependents, they are all possible to move
out of the loop as global variables, although I feel like it would
be easy to move too many things out of the loop.  Then we have
a big loop that we can divide among the threads using the single
argument we were given to start the loop among each of the threads
seperately and have them each work on numloops/numthreads amount
of loops.

When you look at the end goal of this loop, it is to print out
each of the pixel things after processing them, but if you leave
the print in this parallelized loop, race conditions could occur
that make some of the pixels print out of order. To combat this,
we have to store the results somewhere to be printed after
parallelization finishes, so we make a big array to store everything.
Then you just add a loop in the main after this function is done
running so you can print out the stuff you want.

The first issue I had was that I didn't know what to pass in as
the variable for the function.  I thought it might be possible
to use everything as a global variable but after testing for a while
I realized that nthreads is changing so the variable of thread
identifiers based off nthreads would need to change too. Since the
id is based off the specific thread and we have no way to differentiate
outside the main, using that as the arg was the only option that made
sense.

The second thing was a small syntax issue that I didn't even know
how to use this variable I passed in. I looked it up and figured
out how to do that, but the functions passed in as variables are
still confusing to me in general.

I also created a struct for organization since I was pretty certain
that the three floats correspond to RGB, so you can just bunch each
one together as a pixel and it makes a little more sense.

Some of it was kind of difficult to figure out like which parts I
should or should not include in the function but to make it easier
and not mess with anything else, the loop is good to parallelize
and nothing else would make much of a difference on top of it I
assume so that's what I decided on in the end.

Most of the other work was just derived from the previous implementation.


make clean check

time ./srt 1-test.ppm >1-test.ppm.tmp
real    0m47.592s
user    0m47.584s
sys     0m0.001s
mv 1-test.ppm.tmp 1-test.ppm

time ./srt 2-test.ppm >2-test.ppm.tmp
real    0m24.002s
user    0m47.718s
sys     0m0.002s
mv 2-test.ppm.tmp 2-test.ppm

time ./srt 4-test.ppm >4-test.ppm.tmp
real    0m12.347s
user    0m48.533s
sys     0m0.002s
mv 4-test.ppm.tmp 4-test.ppm

time ./srt 8-test.ppm >8-test.ppm.tmp
real    0m6.468s
user    0m50.163s
sys     0m0.003s
mv 8-test.ppm.tmp 8-test.ppm

From the check given to us, you can tell that the real time is heavily
reduced when you use parallelization (almost cut in half each time),
implying that almost all of the work was in that big loop to begin with.
user and sys times rise a little bit with more parallelization but
the real time gets a lot lower in comparison so in the end it's all
worth the effort to parallelize.
