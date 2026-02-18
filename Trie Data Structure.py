# We can call it trie tree or even prefix tree , 
# it is a tree data structure used to store a dynamic set or associative array where the keys are usually strings.
# It is used for searching and storing strings in an efficient way. Each node in the trie represents a common prefix of some keys, 
# and the edges represent the characters of the keys. The root node represents an empty string, 
# and each path from the root to a leaf node represents a key in the trie.

class TrieNode:
    def __init__(self):
        self.children = {}
        self.terminal = False
        
        
        
class Trie:
    def __init__ (self):
        self.root = TrieNode()
        
    def insert(self, word) -> None:
        current_node = self.root
        for char in word:
            if char not in current_node.children:
                current_node.children[char] = TrieNode()
            current_node = current_node.children[char]
        current_node.terminal = True
        
        
    def search(self, word) -> bool:
        current_node = self.root    
        for char in word:
            if char not in current_node.children:
                return False
            current_node = current_node.children[char]
        return current_node.terminal
    
    def starts_with(self, prefix) -> bool:
        current_node = self.root
        for char in prefix:
            if char not in current_node.children:
                return False
            current_node = current_node.children[char]
        return True
    
    
    def _delete (self , curr, word, index) -> bool:
        if index == len(word):
            if not curr.terminal:
                return False
            curr.terminal = False
            return len(curr.children) == 0
        
        char = word[index]
        if char not in curr.children:
            return False
        
        should_delete_child = self._delete(curr.children[char], word, index + 1)
        
        if should_delete_child:
            del curr.children[char]
            return len(curr.children) == 0 and not curr.terminal
        
        return False
    
    def delete(self, word) -> None:
        self._delete(self.root, word, 0)
    
    
    
    
    
    
# test cases 
trie = Trie()
trie.insert("hello")
trie.insert("hell")
trie.insert("he")   

# We can call it trie tree or even prefix tree , 
# it is a tree data structure used to store a dynamic set or associative array where the keys are usually strings.
# It is used for searching and storing strings in an efficient way. Each node in the trie represents a common prefix of some keys, 
# and the edges represent the characters of the keys. The root node represents an empty string, 
# and each path from the root to a leaf node represents a key in the trie.

class TrieNode:
    def __init__(self):
        self.children = {}
        self.terminal = False
        
        
        
class Trie:
    def __init__ (self):
        self.root = TrieNode()
        
    def insert(self, word) -> None:
        current_node = self.root
        for char in word:
            if char not in current_node.children:
                current_node.children[char] = TrieNode()
            current_node = current_node.children[char]
        current_node.terminal = True
        
        
    def search(self, word) -> bool:
        current_node = self.root    
        for char in word:
            if char not in current_node.children:
                return False
            current_node = current_node.children[char]
        return current_node.terminal
    
    def starts_with(self, prefix) -> bool:
        current_node = self.root
        for char in prefix:
            if char not in current_node.children:
                return False
            current_node = current_node.children[char]
        return True
    
    
    def _delete (self , curr, word, index) -> bool:
        if index == len(word):
            if not curr.terminal:
                return False
            curr.terminal = False
            return len(curr.children) == 0
        
        char = word[index]
        if char not in curr.children:
            return False
        
        should_delete_child = self._delete(curr.children[char], word, index + 1)
        
        if should_delete_child:
            del curr.children[char]
            return len(curr.children) == 0 and not curr.terminal
        
        return False
    
    def delete(self, word) -> None:
        self._delete(self.root, word, 0)
        
        
    def PrintTrie(self, node=None, word=""):
        if node is None:
            node = self.root
        if node.terminal:
            print(word)
        for char, child in node.children.items():
            self.PrintTrie(child, word + char)
        
    
    
    
    
    
    
# ... [Your Trie and TrieNode classes go here] ...

def run_test_cases():
    print("Running test cases...")
    
    # --- Test Case 1: Basic Insertion and Search ---
    trie = Trie()
    trie.insert("apple")
    assert trie.search("apple") == True, "Failed to find inserted word 'apple'"
    assert trie.search("app") == False, "'app' should not exist yet (only as prefix)"
    assert trie.search("banana") == False, "Found non-existent word"
    trie.PrintTrie()  # Should print 'apple' only
    print("-" * 50)
    
    # --- Test Case 2: Starts With (Prefix) Logic ---
    assert trie.starts_with("app") == True, "Prefix 'app' should be found"
    assert trie.starts_with("apple") == True, "Full word should also count as prefix"
    assert trie.starts_with("ban") == False, "Non-existent prefix found"
    trie.PrintTrie() 
    print("-" * 50)
    
    # --- Test Case 3: Overlapping Words (The 'Terminal' Flag) ---
    trie.insert("app")
    assert trie.search("app") == True, "Now 'app' should be found as a word"
    assert trie.search("apple") == True, "'apple' should still be found"
    trie.PrintTrie() 
    print("-" * 50)
    
    # --- Test Case 4: Branching Paths ---
    trie.insert("bat")
    trie.insert("ball")
    assert trie.search("bat") == True
    assert trie.search("ball") == True
    assert trie.starts_with("ba") == True
    assert trie.search("ba") == False
    trie.PrintTrie() 
    print("-" * 50)
    
    # --- Test Case 5: Deletion Scenario A (Leaf Node) ---
    # Delete 'bat'. 'ball' should remain.
    trie.delete("bat")
    assert trie.search("bat") == False, "Deleted word 'bat' was found"
    assert trie.search("ball") == True, "'ball' was accidentally deleted"
    assert trie.starts_with("ba") == True, "Prefix 'ba' should still exist for 'ball'"
    trie.PrintTrie() 
    print("-" * 50)
    
    # --- Test Case 6: Deletion Scenario B (Node is a prefix of another) ---
    # Delete 'app'. 'apple' should remain. 
    # This tests if we correctly unmark 'terminal' without deleting children.
    trie.delete("app")
    assert trie.search("app") == False, "'app' should be deleted"
    assert trie.search("apple") == True, "'apple' should remain"
    assert trie.starts_with("app") == True, "Prefix 'app' must remain for 'apple'"
    trie.PrintTrie()
    print("-" * 50)
     
    # --- Test Case 7: Deletion Scenario C (Node has a prefix that is a word) ---
    # Insert 'he', 'hell', 'hello' (Your original example)
    trie2 = Trie()
    trie2.insert("hello")
    trie2.insert("hell")
    trie2.insert("he")
    trie2.PrintTrie() 
    print("-" * 50)
    
    # Delete 'hello' (Leaf deletion, but 'hell' is parent)
    trie2.delete("hello")
    assert trie2.search("hello") == False
    assert trie2.search("hell") == True, "'hell' should remain after deleting 'hello'"
    assert trie2.search("he") == True
    trie2.PrintTrie()
    print("-" * 50)
 
    # Delete 'hell' (Middle node deletion)
    trie2.delete("hell")
    assert trie2.search("hell") == False
    assert trie2.search("he") == True, "'he' should remain"
    trie2.PrintTrie() 
    print("-" * 50)

    # --- Test Case 8: Delete Non-Existent Word ---
    # Should not crash
    trie2.delete("xyz") 
    trie2.delete("heLLo") # Case sensitivity check
    assert trie2.search("he") == True, "Failed deletion logic corrupted the tree"
    trie2.PrintTrie() 
    print("-" * 50)
    
    print("✅ All test cases passed!")

if __name__ == "__main__":
    run_test_cases()