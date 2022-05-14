import java.util.*;
import java.io.*;

class Node implements Comparable<Node> {
    int adj;
    int weight;
    int parent;
    int edgeQuery;
    boolean known;
    Node next;
    
    public int compareTo(Node n) {
        if(this.weight < n.weight){
            return -1;
        }else if(this.weight > n.weight){
            return 1;
        }else
            return 0;
    }
}


class LinkedList {
    Node head = null;
    Node tail = null;

    public void add(Node newNode) {
        //Checks if the list is empty
        if (head == null) {
            //If list is empty, both head and tail will point to new node
            head = newNode;
            tail = newNode;
            tail.next = null;

        } else {
            //newNode will be added after tail such that tail's next will point to newNode
            tail.next = newNode;
            //newNode will become new tail of the list
            tail = newNode;
            tail.next = null;
        }
    }
    public void removeLastNode()
    {
        // Find the second last node
        Node second_last = head;
        while (second_last.next.next != null)
            second_last = second_last.next;

        // Change next of second last
        second_last.next = null;
        tail = second_last;
    }
}


public class oc {

        public static void read_input(ArrayList<LinkedList> graph, ArrayList<Node> query, String args) throws IOException {
            int pos, num;
            String line;
            Scanner scanner = new Scanner(new File(args));
            pos = scanner.nextInt();
            for (int i = 0; i < pos + 1; i++) {
                LinkedList a = new LinkedList();
                graph.add(a);
                Node u = new Node();   // representatives nodes
                u.adj = i;
                u.parent = -1;
                u.weight = Integer.MAX_VALUE;
                graph.get(i).add(u);
            }
        
            line = scanner.nextLine();
            for(int i = 0; i<pos-1; i++) {
                line = scanner.nextLine();
                copyNodes(line, graph);
            }    
            pos = scanner.nextInt();
            line = scanner.nextLine();
            for(int i = 0; i<pos; i++) {
                line = scanner.nextLine();
                Node newNode = new Node();
                Scanner scanner2 = new Scanner(line);
                newNode.edgeQuery = scanner2.nextInt();
                newNode.adj = scanner2.nextInt();
                newNode.weight = scanner2.nextInt();
                query.add(newNode);
                scanner2.close();
            }
            scanner.close();
        }

        public static void insert_node(int pos, int adj, int weight, ArrayList<LinkedList> graph) {
                Node newNode = new Node();
                newNode.adj= adj;
                newNode.weight = weight;
                LinkedList temp = graph.get(pos);
                temp.add(newNode);
            }

        public static void copyNodes(String line, ArrayList<LinkedList> graph) {
            int pos,adj, weight;
            Scanner scanner2 = new Scanner(line);
            pos = scanner2.nextInt();
            adj = scanner2.nextInt();
            weight = scanner2.nextInt();
            scanner2.close();
            insert_node(pos, adj, weight, graph);
            insert_node(adj, pos, weight, graph);
        }

     public static void makeQueries(ArrayList<LinkedList> graph, ArrayList<Node> query, String args) throws IOException{
        boolean betterEdge;
        PrintWriter writer = new PrintWriter(new File(args));  
        for (int i = 0; i < query.size(); i++) {
            Node currQuery = query.get(i);       
            Node node = graph.get(currQuery.adj).head;    //take the current node to query
            betterEdge = setBetterEdge(graph, currQuery.weight, node);
            if(betterEdge == false){  // if we have not find a bigger weight in the first path node, we search in the brother's path 
                node = graph.get(currQuery.edgeQuery).head; // brother
                betterEdge = setBetterEdge(graph, currQuery.weight, node);
            }
            // PRINT:
            if(betterEdge == true){
                writer.println("YES");
            }else{
                writer.println("NO");
            }
        }
        writer.close();
    }


    public static boolean setBetterEdge(ArrayList<LinkedList> graph, int weight, Node node){
        while(node.parent > 0){   // visit the path of that node
            if(weight < node.weight)
                return  true;
            node = graph.get(node.parent).head;    // node becomes the parent of the previous node 
        }        
        return  false;
    }


    public static void prim(ArrayList<LinkedList> graph, int pos){
        PriorityQueue<Node> pq = new PriorityQueue<Node>();
        Node root = graph.get(pos).head;
        root.weight = 0;
        root.parent = 0;
        for(int i = 1; i < graph.size(); i++) // Fill the queue with the nodes
            pq.add(graph.get(i).head);
        while(!pq.isEmpty()){
            Node u = pq.remove();
            setBrothers(graph, pq, u);
            u.known = true;
        }
    }


    public static void setBrothers(ArrayList<LinkedList> graph,PriorityQueue<Node> pq, Node u){
        Node brother = u.next;
        while(brother != null){
            Node vertex = graph.get(brother.adj).head; // i set only the head of the graph 
            if(vertex.known == false && brother.weight < vertex.weight){
                vertex.parent = u.adj;          //set new path
                vertex.weight = brother.weight; //set new weight
                pq.remove(vertex); // The vertex is modified, so i have to re-add it
                pq.add(vertex);
            }
            brother = brother.next;   
        }    
    }

    public static int takeRoot(String args) throws IOException{
        Scanner scanner = new Scanner(new File(args));
        int root = scanner.nextInt();
        root = scanner.nextInt();
        scanner.close();
        return root;
    }

    public static void main(String args[]) throws IOException {
        ArrayList<Node> query = new ArrayList<Node>();
        ArrayList<LinkedList> graph = new ArrayList<LinkedList>();
        read_input(graph, query, args[0]);
        int root = takeRoot(args[0]);
        prim(graph, root);
        makeQueries(graph, query, args[1]);
    }
}
