# Initial Thumb mask and entry selection

The learner correctly converts 1u << 24 to hexadecimal 0x01000000 and predicts that a frame with A's entry address in its PC slot starts A even when intended for B. These demonstrate mask conversion and the effect of the initial PC value; the next step is to observe a real exception frame before building a first-task initializer.
