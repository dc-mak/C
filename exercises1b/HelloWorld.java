class HelloWorld {
	public native void display();
	static { System.loadLibrary("hello"); }
	public static void main(String[] args) {
		new HelloWorld().display();
	}
}
