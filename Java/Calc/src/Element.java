public class Element<T>
{
    private T x;
    private Element parent;
    private int depth;

    public Element(T x)
    {
        this.x = x;
        this.parent = this;
        this.depth = 0;
    }

    public T x()
    {
        return this.x;
    }


    public boolean equivalent(Element<T> elem)
    {
        return this.find().equals(elem.find());
    }

    public Element<T> find(){
        if(this.parent.equals(this)){
            return this;
        }
        else{
            return this.parent = this.parent.find();
        }
    }

    public void union(Element<T> elem)
    {
        Element root = this.find(), rootElem = elem.find();
        if(root.depth < rootElem.depth)
            root.parent = rootElem;
        else{
            rootElem.parent = root;
            if(root.depth == rootElem.depth && !root.equals(rootElem)){
                root.depth++;
            }
        }
    }
}