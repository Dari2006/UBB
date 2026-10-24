package ui;

import Domain.Friendship;
import Domain.User;
import repository.FriendshipRepository;
import service.FriendshipService;
import service.NetworkService;
import service.UserService;

import java.util.List;
import java.util.Scanner;

public class ConsoleUI {

    private UserService userService;
    private FriendshipService friendshipService;
    private Scanner scanner;
    private NetworkService networkService;

    public ConsoleUI(UserService userService,
                     FriendshipService friendshipService,
                     NetworkService networkService) {

        this.userService = userService;
        this.friendshipService = friendshipService;
        this.networkService = networkService;
        this.scanner = new Scanner(System.in);
    }



    public void run() {
        while (true) {
            printMenu();

            String option = scanner.nextLine();

            try {
                switch (option) {
                    case "1":
                        addUser();
                        break;
                    case "2":
                        showUsers();
                        break;
                    case "3":
                        deleteUser();
                        break;
                    case "4":
                        addFriendship();
                        break;
                    case "5":
                        deleteFriendship();
                        break;
                    case "6":
                        showNumberOfCommunities();;
                        break;
                    case "7":
                        showMostSocialCommunity();
                        break;
                    case "0":
                        return;
                    default:
                        System.out.println("Invalid option");
                }
            } catch (RuntimeException e) {
                System.out.println("Error: " + e.getMessage());
            }
        }
    }

    private void printMenu() {
        System.out.println("""
                1. Add user
                2. Show users
                3. Delete user
                4. Add friendship
                5. Delete friendship
                6. Show number of communities
                7. Show largest community
                0. Exit
                """);
    }

    private void addUser() {

        System.out.print("First name: ");
        String firstName = scanner.nextLine();

        System.out.print("Last name: ");
        String lastName = scanner.nextLine();

        System.out.print("Username: ");
        String username = scanner.nextLine();

        userService.addUser(firstName, lastName, username);

        System.out.println("User added!");
    }

    private void showUsers() {

        Iterable<User> users = userService.getAllUsers();
        boolean empty = true;

        for (User user : users) {
            System.out.println(user);
            empty = false;
        }

        if (empty) {
            System.out.println("No users found.");
        }
    }

    private void deleteUser() {

        System.out.print("User id: ");
        Long id = Long.parseLong(scanner.nextLine());

        userService.deleteUser(id);

        System.out.println("User deleted!");
    }

    private void addFriendship() {

        System.out.print("First user id: ");
        Long user1Id = Long.parseLong(scanner.nextLine());

        System.out.print("Second user id: ");
        Long user2Id = Long.parseLong(scanner.nextLine());

        friendshipService.addFriendship(user1Id, user2Id);

        System.out.println("Friendship added!");
    }

    private void deleteFriendship() {

        System.out.print("Friendship id: ");
        Long id = Long.parseLong(scanner.nextLine());

        friendshipService.deleteFriendship(id);

        System.out.println("Friendship deleted!");
    }

    private void showNumberOfCommunities() {
        int number = networkService.getNumberOfCommunities();

        System.out.println("Number of communinties: " + number);
    }

    private void showMostSocialCommunity() {
        List<User> community = networkService.getMostSocialCommunity();

        System.out.println("Most social community:");

        if (community == null || community.isEmpty()) {
            System.out.println("No communities exist");
            return;
        }

        for (User user : community) {
            System.out.println(user);
        }
    }
}