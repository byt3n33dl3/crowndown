import java.util.ArrayList;
import java.util.Scanner;

public class ListManagementSystem {
    private ArrayList<String> itemList;

    public ListManagementSystem() {
        itemList = new ArrayList<>();
    }

    public void addItem(String item) {
        itemList.add(item);
        System.out.println(item + " has been added to the list.");
    }

    public void removeItem(String item) {
        if (itemList.remove(item)) {
            System.out.println(item + " has been removed from the list.");
        } else {
            System.out.println(item + " is not in the list.");
        }
    }

    public void displayList() {
        if (itemList.isEmpty()) {
            System.out.println("The list is empty.");
        } else {
            System.out.println("List items:");
            for (String item : itemList) {
                System.out.println("- " + item);
            }
        }
    }

    public static void main(String[] args) {
        ListManagementSystem listManager = new ListManagementSystem();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("\nChoose an option:");
            System.out.println("1. Add item");
            System.out.println("2. Remove item");
            System.out.println("3. Display list");
            System.out.println("4. Exit");

            int choice = scanner.nextInt();
            scanner.nextLine();  // Consume the newline character

            switch (choice) {
                case 1:
                    System.out.println("Enter item to add:");
                    String addItem = scanner.nextLine();
                    listManager.addItem(addItem);
                    break;
                case 2:
                    System.out.println("Enter item to remove:");
                    String removeItem = scanner.nextLine();
                    listManager.removeItem(removeItem);
                    break;
                case 3:
                    listManager.displayList();
                    break;
                case 4:
                    System.out.println("Exiting the List Management System. Goodbye!");
                    scanner.close();
                    System.exit(0);
                default:
                    System.out.println("Invalid choice. Please choose a valid option.");
            }
        }
    }
}
