public class Node {
  private int data;
  private Node left;
  private Node right;
public int getData()  {
    return data;
  }
  
  public Node getLeft()  {
    return left;
  }

    public Node getRight()  {
    return right;
  }
 
  public void setData(int x)  {
    data = x;
  }
public void setLeft(Node p)  {
    left = p;
  }

  public void setRight(Node p)  {
    right = p;
  }


}
public class Tree {
    private Node root;
    
    // tree() - The default constructor – Starts
    //          the tree as empty
    
    public Tree() {
        root = null;
    }
    
    // Tree() - An initializing constructor that
    //          creates a node and places in it
    //          the initial value
    public Tree(int x) {
        root = new Node();
        root.setData(x);
        root.setLeft(null);
        root.setRight(null);
    }
    
    public Node getRoot() {
        return root;
    }
    
    // newNode() -  Creates a new node with a
    //              zero as data by default
    public Node newNode() {
        Node p = new Node();
        p.setData(0);
        p.setLeft(null);
        p.setRight(null);
        return(p);
    }
    // newNode() -  Creates a new node with the
    //              parameter x as its value
    public Node newNode(int x)  {
        Node p = new Node();
        p.setData(x);
        p.setLeft(null);
        p.setRight(null);
        return(p);  
    }
    //travTree() – initializes recursive 
    //	traversal of tree
	  public void  travTree() {
        if (root != null)
          travSubtree(root);
        System.out.println();
    }
    //travSubtree() – recursive method used to 
	  //	traverse a binary tree (inorder)
    public void  travSubtree(Node p) {
        if (p != null)  {
            travSubtree(p.getLeft());
            System.out.print(p.getData() 
						+ "\t");
            travSubtree(p.getRight());
        } 
    }
    // addLeft() -  Inserts a new node containing
    //              x as the left child of p
    public void  addLeft(Node p, int x) {
        Node   q = newNode(x);
        p.setLeft(q);
    }
    
	 // addRight() -  Inserts a new node containing
   //                x as the right child of p
    public void  addRight(Node p, int x) {
        Node   q = newNode(x);
        p.setRight(q);
    }
}
    // insert() -	Insert value x in a new node to
    //				be inserted	after p
    public void	insert(int x)  {
        Node 	p, q;
        boolean	found = false;
        p = root;
        q = null;
        while (p != null && !found)	{
            q = p;
            if (p.getData() == x)
              found = true;
            else if (p.getData() > x)
              p = p.getLeft();
            else
              p = p.getRight();
        }
        if (found)
          error("Duplicate entry");
          
        if (q.getData() > x)
          addLeft(q, x);
        else
          addRight(q, x);
        
        //q = newNode(x);
    }
    // isXThere() -	Is there a node in the
    //                  tree containing x?
    public boolean	isXThere(int x)  {
        Node 	p;
        boolean	found = false;
        p = root;
        while (p != null && !found)	{
            if (p.getData() == x)
              found = true;
            else if (p.getData() > x)
              p = p.getLeft();
            else
              p = p.getRight();
        }
        return(found);
    }
    
    public void	error(String message) {
	    System.out.println(message);
	    System.exit(0);
    }
    // getNode() -	Get the pointer for the
    //                  node containing x
    public Node	getNode(int x) {
        Node 	p, q;
        boolean	found = false;
        
        p = root;
        q = null;
        while (p != null && !found)	{
            q = p;
            if (p.getData() == x)
			  found = true;
			else if (p.getData() > x)
			  p = p.getLeft();
			else
			  p = p.getRight();
		}
	if (found)
		  return(q);
		else
		  return(null);
    }
public class TestTree {
    public static void main(String[] args) {
        Tree	mytree = new Tree(8);
        mytree.addLeft(mytree.getRoot(), 6);
        mytree.addRight(mytree.getRoot(), 9);
        mytree.insert(4);
        mytree.insert(1);
        mytree.insert(12);
        
        if (mytree.isXThere(13))
          System.out.println("great");
        else 
		    System.out.println("not great, Bob");
        mytree.travTree();
    }
}
