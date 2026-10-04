# Counting iterations of the startup data copy

The learner correctly identifies _edata as the end and predicts two four-byte copies for a destination range from 0x20000000 to 0x20000008. They also identify bcc as branch carry clear. They initially treated equality as satisfying strict less-than; after correction, they correctly predict zero copies when start equals end. Recheck a nonempty boundary in a later retrieval exercise; comparison flags have not yet been independently traced.
