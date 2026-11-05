import Config.Config;
import Domain.Friendship;
import Domain.User;
import repository.FriendshipRepository;
import repository.Repository;
import repository.RepositoryFactory;
import repository.UserRepository;
import repository.fileRepository.FriendshipFileRepository;
import repository.fileRepository.UserFileRepository;
import service.FriendshipService;
import service.NetworkService;
import service.UserService;
import ui.ConsoleUI;
import validator.FriendshipValidator;
import validator.UserValidator;

public class Main {

    public static void main(String[] args) {

        UserValidator userVal = new UserValidator();
        FriendshipValidator friendshipVal = new FriendshipValidator();
        Config config = new Config();

        RepositoryFactory repoFact = new RepositoryFactory(config.getProperties());
        Repository<Long, User> repoUser = repoFact.createUserRepository(userVal);
        Repository<Long, Friendship> friendshipRepo = repoFact.createFriendshipRepository(friendshipVal);

        UserService userService = new UserService(repoUser, userVal);
        FriendshipService friendshipService = new FriendshipService(friendshipRepo, repoUser, friendshipVal);
        NetworkService networkService = new NetworkService(repoUser, friendshipRepo);
        ConsoleUI ui = new ConsoleUI(userService, friendshipService, networkService);

        ui.run();
    }
}