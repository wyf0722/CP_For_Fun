// 饿汉式
class Singleton {
    private volatile static Singleton INSTANCE = new Singleton();

    private Singleton() {

    }

    public static Singleton getInstance() {
        return INSTANCE;
    }
}

// 双重校验
class Singleton {
    private volatile static Singleton INSTANCE;

    private Singleton() {

    }

    public static Singleton getInstance() {
        if (INSTANCE == null) {
            synchronized (Singleton.class) {
                if (INSTANCE == null) {
                    INSTANCE = new Singleton();
                }
            }
        }
        return INSTANCE;
    }
}

// 内部类
class Singleton {
    private Singleton() {

    }

    private static class Inner {
        private static Singleton INSTANCE = new Singleton();
    }

    public static Singleton getInstance() {
        return Inner.INSTANCE;
    }
}