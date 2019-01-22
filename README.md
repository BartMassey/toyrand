# toyrand: Entropy-pool Game PRNG
Copyright (c) 2019 Bart Massey

This pseudorandom number generator is designed for use in
casual games and simulations. Misfeatures and features:

* Uses a selectable-size state seeded from a true RNG.

  * See "Use Case" below.

  * Seeding will not work without a true RNG. Depending on
    compile-time flags `toyrand` will try to do seeding with
    the `RDRAND` x86 CPU instruction, failing that with
    `/dev/urandom`. Patches for other RNGs are welcome.

* Vaguely principled. Uses an underlying hash with some
  known properties to update the entropy pool. More
  evaluation is needed.

* Lightly tested. Completely "passes
  [DieHarder](https://webhome.phy.duke.edu/~rgb/General/dieharder.php)"
  for whatever that is worth. More testing is needed.

* Reasonable C code. No warnings. Testdriver passes
  `valgrind`. Comments deperately needed.

* Fast-ish: Cost of 1 32x32 multiply, one rotate, one add,
  two 32-bit reads and a 32-bit write per generated variate.
  1 billion variates per second on my modern box with
  everything in cache.

* Not splittable, no jump-ahead.

* Definitely *not* known to be cryptographically secure.

## Use Case

It is common to need to produce an arbitrary instance of a
large combinatorial object using a PRNG. Consider shuffling
a deck of cards: one would like use a PRNG to produce with
uniform probability any of the 72! possible permutations of
the deck. Information theory tells us that this would
require *log2(72!)* (a little less than 226) bits of seed
and internal state in the PRNG used. Less than that and some
permutations are provably unreachable by any PRNG method.

This issue is regularly noted in the literature on
randomization, especially in games and simulations. The
advice is generally to exceed the information-theoretic
bound substantially, to cover possible flaws in the PRNG and
construction algorithms. Unfortunately, in a moderately
diligent search I could not find off-the-shelf PRNGs that
supported large internal state sizes.

As far as I know, the missing-information flaw has no
practical implication for a decent generator: I can't see
any obvious way to observe the flaw externally without
constructing some implausibly large statistical
enumerations, since the whole point of a good PRNG is to be
uncorrelated with everything and there are plenty of good
PRNGs with 64-bit state and seeds. That said, it seems
better to err on the side of caution, which is what this
generator does.

This generator *should not be used* when:

* Adversary attack is an issue: the security of `toyrand` is
  *unknown*.

* Critical resources are in play: `toyrand` has not been
  subjected to any kind of rigorous analysis, and may have
  horrible undiscovered flaws.

* Fancy generator features such as skip-ahead and splitting
  are needed: `toyrand` doesn't do that.

* A well-known high-quality generator will do the job: in
  addition to the problems listed above, this is extra
  machinery to bring in.

## Utilities

* `toyprint` writes pseudo-random variates to standard
  output. Can use hex ASCII or native-endian (shouldn't
  matter, because random) binary. Selectable output count or
  infinite output. Selectable pool size.

* `toybench` xors together a specified number of variates
  and prints the result. This enables using system timing
  routines or a stopwatch to get a microbenchy and suspect
  view of performance.

## Build, Install, Use

Before building, check the `DEFINES` in the `Makefile` to
ensure that you have configured for the environment. You
should choose at least one of `-DRDRAND` and `-DURANDOM`:
both can be used on an appropriate architecture (`RDRAND`
will be tried first).

On a Linux box, type `make`. To make `toyprint` and run
Dieharder, install the Dieharder executable driver (Debian
package `dieharder`) and then type `make test`. To make
`toybench`, say `make toybench`. To test RDRAND support say
`make testrdrand` and run it.

To install, check the paths in the `Makefile` and then say
`make install` with appropriate permissions.  To use,
include `toyrand.h` in your C program and link against the
library.

Manual pages are desperately needed.

## License

This program is licensed under the "MIT License". Please see
the file `LICENSE` in this distribution for license terms.
