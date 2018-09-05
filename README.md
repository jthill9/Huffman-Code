Homework 07
===========

# Activity 2 - Questions

1. Describe how the `symbol` is stored in the `Node` **struct** by diagramming
   the memory layout of the following `Node` structure:

   Symbol is stored in 8 bytes of a Node's total 32 bytes. count takes up
   another 8 bytes since it is an unsigned int, and left and right both take up
   8 bytes because they are pointers. Also, all of these members of the struct
   are stored continuously in memory. In the following example, the node is
   dynamically allocated to the heap since we call malloc in node_create and
   allocate the size of a Node. In the symbol, the backlash and the n end up
   being stored separately, as two different characters, so that they do not
   represent a newline in the symbol anymore.

        Node *n = node_create('\n', 2, NULL, NULL);

    Be sure to indicate how much memory each `Node` structure occupies and how
    much is allocated for each attribute in the struct.

    1. Explain what the code `assert(n->symbol.letter == '\n')` would result in?

    The way we store characters in symbol, this assert statement would fail. We
    never actually store any of the escaped characters, in this case the new
    line character, in the union. Instead, we store the backslash and the n
    characters separately, which will not be recognized as being equal to the
    newline character.

    2. Given that `symbol` is a **union** type, is it ever possible for both the
      `letter` and `string` of the symbol `\n` to co-exist (that is, the
      `string` doesn't clobber the `letter`)?

        **Hint**: Consider alternative architectures.

    It is not possible for the letter and the string to coexist as two separate
    things. When we assign letter equal to newline in this case for instance,
    we then overwrite that when we assign the string part of the symbol. There
    will not be any times that we change string and it does not clobber the
    letter part of the union. This happens because a union stores all of its
    members in the same location of memory, not allowing them to be different as
    something like a struct would.

2. To construct the Huffman code, you had to utilize both a **priority queue**
   (aka. **min-heap**) and a **Huffman Tree**, both of which were binary trees.
   For the former, you used an **array** representation while for the later you
   used a **linked node** representation.  With this in mind, answer the
   following questions:

    1. Would it have been easier to implement the **priority queue** with a
      **linked node** representation?  Explain why this would be better or
      worse than the **array** representation.

      I do not think that it would have been easier to implement the priority
      queue with a linked node representation. When we were bubbling up and
      down it would have been much more difficult than using the array
      representation. As opposed to doing a simple swap in an array using a temp
      variable, we would have had to keep track of three nodes at a time to be
      able to switch around all of their pointers while moving the nodes up or
      down in the priority queue.

    2. Would it have been easier to implement the **Huffman Tree** with an
      **array** representation?  Explain why this would be better or worse
      than the **linked node** representation.

      I don't think it would have been easier to implement the Huffman Tree
      with an array representation. It would have been more difficult to insert
      into the array, as all we have to do now is create a new Node and assign
      its children. It also would have been harder to print out all of the nodes
      and walk the tree, as recursion is much easier when we have linked nodes
      than an array. It would also waste space because an array representation
      allocates enough space for a complete tree even though the Huffman will
      always have lots of empty space on the left side. That space is wasted in
      the array representation but is never unnecessarily allocated if we use
      the linked node representation.

3. Analyze the results of your experiments with you `huff.py` Python script.
   What sort of compression ratios were you able to achieve?  How does this
   compare to standard utilities such as `gzip`, `bzip2`, and `xz`?

huff:
    |        FILE        | OLD SIZE | NEW SIZE |   RATIO   |
    |--------------------|----------|----------|-----------|
    |         alice.ascii|   1316256|    762209|     57.91%|
    |         frank.ascii|   3579976|   2005480|     56.02%|
    |         heart.ascii|   1866304|   1065323|     57.08%|
    |         pride.ascii|   5712504|   3238750|      56.7%|
    |          tale.ascii|   6298296|   3575846|     56.77%|

    All of the compressions reduced the size of the files to between 56 and 58
    percent of the original.

gzip:
    |        FILE        | OLD SIZE | NEW SIZE |   RATIO   |
    |--------------------|----------|----------|-----------|
    |         alice.ascii|   1316256|    475056|     36.09%|
    |         frank.ascii|   3579976|   1350104|     37.71%|
    |         heart.ascii|   1866304|    744280|     39.88%|
    |         pride.ascii|   5712504|   2063288|     36.12%|
    |          tale.ascii|   6298296|   2386248|     37.89%|


bzip2:
    |        FILE        | OLD SIZE | NEW SIZE |   RATIO   |
    |--------------------|----------|----------|-----------|
    |         alice.ascii|   1316256|    385208|     29.27%|
    |         frank.ascii|   3579976|   1009360|     28.19%|
    |         heart.ascii|   1866304|    591600|     31.70%|
    |         pride.ascii|   5712504|   1443303|     25.27%|
    |          tale.ascii|   6298296|   1750608|     27.79%|


xz:
    |        FILE        | OLD SIZE | NEW SIZE |   RATIO   |
    |--------------------|----------|----------|-----------|
    |         alice.ascii|   1316256|    422944|     32.13%|
    |         frank.ascii|   3579976|   1134720|     31.70%|
    |         heart.ascii|   1866304|    652672|     34.97%|
    |         pride.ascii|   5712504|   1675936|     29.33%|
    |          tale.ascii|   6298296|   1973888|     31.34%|     

    bzip2 was the most effective, followed by xz, gzip, and then our huff
    program. All three of the given ones were in the 20s or 30s as a percent of
    the size of the original. All three of theose were better then huff, which
    as stated before only compressed each file to between 50 and 60 percent of
    its original size.
