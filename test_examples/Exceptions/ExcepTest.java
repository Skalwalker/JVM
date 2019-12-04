public class ExcepTest {
    public static void arrayoutbounds() {
        int a[] = new int[2];
        try {
            a[-1] = 0;
        } catch (ArrayIndexOutOfBoundsException e) {
            throw new ArrayIndexOutOfBoundsException();
        }
        // System.out.println(a[3]);
    }

    public static void arraynull() {
        int a[] = null;
        try {
            a[3] = 7;
        } catch (NullPointerException e) {
            System.out.println(e);
        }
    }

    public static void negativeArraySize() {
        int a[] = new int[-2];
    }

    public static void arraystore() {
        Object[] s = new Puppy[2];
        s[0] = new Catto();
    }

    public static void arithmetic() {
        float a = (3.0f / 0.0f);
    }

   public static void main(String[] args) {
       // arraynull();
       // arraystore();
       negativeArraySize();
       // arrayoutbounds();
   }
}
