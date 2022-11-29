# Level 07

Level 07's program is a number storer/reader.
It stores the numbers in an `char v6[400]` but it doesn't do bounds checking, so we have to take advantage of that.

It does do some checking, namely if the index is divisible by 3 or if HIBYTE(index) == 183 we are not allowed to write there.
But we can bypass that by giving indices which are bigger than INT_MAX.

To be continued...