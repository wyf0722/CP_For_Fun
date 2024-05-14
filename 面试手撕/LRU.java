class LRUCache {
    static class Node {
        int key = 0, value = 0;
        Node prev, next;
        Node(int key_, int value_) {
            key = key_;
            value = value_;
        }
    }

    int capacity;
    HashMap<Integer, Node> hash = new HashMap<>();
    Node dummy = new Node(0, 0);

    public LRUCache(int capacity) {
        dummy.prev = dummy;
        dummy.next = dummy;
        this.capacity = capacity;
    }
    
    public int get(int key) {
        Node node = getNode(key);
        return node == null ? -1 : node.value;
    }
    
    public void put(int key, int value) {
        Node node = getNode(key);
        if (node != null) {
            node.value = value;
            return;
        }
        node = new Node(key, value);
        hash.put(key, node);
        pushFront(node);
        if (hash.size() > capacity) {
            Node last = dummy.prev;
            hash.remove(last.key);
            remove(last);
        }
    }

    public Node getNode(int key) {
        if (!hash.containsKey(key)) {
            return null;
        }
        Node node = hash.get(key);
        remove(node);
        pushFront(node);
        return node;
    }

    public void remove(Node node) {
        node.prev.next = node.next;
        node.next.prev = node.prev;
    }

    public void pushFront(Node node) {
        node.prev = dummy;
        node.next = dummy.next;
        node.prev.next = node;
        node.next.prev = node;
    }
}