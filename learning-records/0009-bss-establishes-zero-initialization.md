# BSS clearing establishes zero initialization

The learner initially predicted garbage for a file-scope int without an explicit initializer. After distinguishing static-storage globals from uninitialized automatic locals, they correctly identify writing zeros to the variable's memory as the operation that establishes its initial zero value. Recheck the C distinction later; next trace the concrete BSS store loop and its address increments.
