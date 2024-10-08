import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.*;

// https://codeforces.com/profile/SecondThread
public class Main {

    public static void main(String[] subscribeToSecondThread) {
        FastScanner fs = new FastScanner();
        PrintWriter out = new PrintWriter(System.out);
        // usage:fs.nextInt()... out.println()
        int t = 1;
//        t = fs.nextInt();
        while (t-- > 0) {
            int n = fs.nextInt();
            long x = fs.nextLong();
            long d = 0;
            for (int i = 0; i < n; i++) {
                long a = fs.nextLong();
                if (x > 0) {
                    x -= a;
                    d += a;
                } else if (x < 0) {
                    x += a;
                    d += a;
                }
            }
            out.println(d);
        }
        out.close();
    }

    static final Random random = new Random();
    static final int mod = 1_000_000_007;

    static void ruffleSort(int[] a) {
        int n = a.length;// shuffle, then sort
        for (int i = 0; i < n; i++) {
            int oi = random.nextInt(n), temp = a[oi];
            a[oi] = a[i];
            a[i] = temp;
        }
        Arrays.sort(a);
    }

    static long add(long a, long b) {
        return (a + b) % mod;
    }

    static long sub(long a, long b) {
        return ((a - b) % mod + mod) % mod;
    }

    static long mul(long a, long b) {
        return (a * b) % mod;
    }

    static long exp(long base, long exp) {
        if (exp == 0)
            return 1;
        long half = exp(base, exp / 2);
        if (exp % 2 == 0)
            return mul(half, half);
        return mul(half, mul(half, base));
    }

    static long[] factorials = new long[2_000_001];
    static long[] invFactorials = new long[2_000_001];

    static void precompFacts() {
        factorials[0] = invFactorials[0] = 1;
        for (int i = 1; i < factorials.length; i++)
            factorials[i] = mul(factorials[i - 1], i);
        invFactorials[factorials.length - 1] = exp(factorials[factorials.length - 1], mod - 2);
        for (int i = invFactorials.length - 2; i >= 0; i--)
            invFactorials[i] = mul(invFactorials[i + 1], i + 1);
    }

    static long nCk(int n, int k) {
        return mul(factorials[n], mul(invFactorials[k], invFactorials[n - k]));
    }

    static void sort(int[] a) {
        ArrayList<Integer> l = new ArrayList<>();
        for (int i : a)
            l.add(i);
        Collections.sort(l);
        for (int i = 0; i < a.length; i++)
            a[i] = l.get(i);
    }

    static class FastScanner {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer("");

        String next() {
            while (!st.hasMoreTokens())
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        int[] readArray(int n) {
            int[] a = new int[n];
            for (int i = 0; i < n; i++)
                a[i] = nextInt();
            return a;
        }

        long nextLong() {
            return Long.parseLong(next());
        }
    }

    //change to System.getProperty("ONLINE_JUDGE")==null; for CodeForces
    // @link: https://codeforces.com/blog/entry/80965
    public static final boolean LOCAL = true;

    private static <T> String ts(T t) {
        if (t == null) {
            return "null";
        }
        try {
            return ts((Iterable) t);
        } catch (ClassCastException e) {
            if (t instanceof int[]) {
                String s = Arrays.toString((int[]) t);
                return "{" + s.substring(1, s.length() - 1) + "}";
            } else if (t instanceof long[]) {
                String s = Arrays.toString((long[]) t);
                return "{" + s.substring(1, s.length() - 1) + "}";
            } else if (t instanceof char[]) {
                String s = Arrays.toString((char[]) t);
                return "{" + s.substring(1, s.length() - 1) + "}";
            } else if (t instanceof double[]) {
                String s = Arrays.toString((double[]) t);
                return "{" + s.substring(1, s.length() - 1) + "}";
            } else if (t instanceof boolean[]) {
                String s = Arrays.toString((boolean[]) t);
                return "{" + s.substring(1, s.length() - 1) + "}";
            }
            try {
                return ts((Object[]) t);
            } catch (ClassCastException e1) {
                return t.toString();
            }
        }
    }

    private static <T> String ts(T[] arr) {
        StringBuilder ret = new StringBuilder();
        ret.append("{");
        boolean first = true;
        for (T t : arr) {
            if (!first) {
                ret.append(", ");
            }
            first = false;
            ret.append(ts(t));
        }
        ret.append("}");
        return ret.toString();
    }

    private static <T> String ts(Iterable<T> iter) {
        StringBuilder ret = new StringBuilder();
        ret.append("{");
        boolean first = true;
        for (T t : iter) {
            if (!first) {
                ret.append(", ");
            }
            first = false;
            ret.append(ts(t));
        }
        ret.append("}");
        return ret.toString();
    }

    public static void debug(Object... o) {
        if (LOCAL) {
            System.out.print("Line #" + Thread.currentThread().getStackTrace()[2].getLineNumber() + ": [");
            for (int i = 0; i < o.length; i++) {
                if (i != 0) {
                    System.out.print(", ");
                }
                System.out.print(ts(o[i]));
            }
            System.out.println("]");
        }
    }
}