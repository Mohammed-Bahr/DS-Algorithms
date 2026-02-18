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
    