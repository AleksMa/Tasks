public class Test {
    public static void main(String[] args) {
        SingleLinkedList<Integer> a = new SingleLinkedList<>();
        for(int i = 9; i >= 0; i--)
            a.insertBeforeHead(i);

        for(int i : a) {
            for (int j : a)
                System.out.print("(" + i + " " + j + ")  ");
            System.out.println();
        }


        a.insertAfter(a.search(2), 10);

        for(int j : a)
            System.out.print(j+" ");

        System.out.println();


        SingleLinkedList<String> b = new SingleLinkedList<>();
        b.insertBeforeHead("Natasha");
        b.insertBeforeHead("Olya");
        b.insertBeforeHead("Nastya");
        b.insertBeforeHead("Ira");
        b.insertBeforeHead("Uma");
        b.insertBeforeHead("Sasha");
        for(String item : b)
            System.out.println(item);
    }
}
