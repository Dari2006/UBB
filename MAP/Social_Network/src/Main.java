import repository.FriendshipRepository;
import repository.UserRepository;
import service.FriendshipService;
import service.UserService;
import ui.ConsoleUI;
import validator.FriendshipValidator;
import validator.UserValidator;

public class Main {

    public static void main(String[] args) {

        UserRepository userRepository = new UserRepository();
        FriendshipRepository friendshipRepository = new FriendshipRepository();

        UserService userService = new UserService(
                userRepository,
                new UserValidator()
        );

        FriendshipService friendshipService = new FriendshipService(
                friendshipRepository,
                userRepository,
                new FriendshipValidator()
        );

        ConsoleUI ui = new ConsoleUI(
                userService,
                friendshipService
        );

        ui.run();
    }
}