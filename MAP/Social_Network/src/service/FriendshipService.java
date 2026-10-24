package service;

import Domain.Friendship;
import Domain.User;
import repository.Repository;
import validator.Validator;

import java.time.LocalDateTime;

public class FriendshipService {

    private Repository<Long, Friendship> friendshipRepository;
    private Repository<Long, User> userRepository;
    private Validator<Friendship> validator;
    private Long nextId;

    public FriendshipService(
            Repository<Long, Friendship> friendshipRepository,
            Repository<Long, User> userRepository,
            Validator<Friendship> validator) {

        this.friendshipRepository = friendshipRepository;
        this.userRepository = userRepository;
        this.validator = validator;
        nextId = 1L;
    }

    private Long generateId() {
        Iterable<Long> keys = friendshipRepository.getKeys();
        Long max = 0L;
        for(Long id : keys){
            if(id > max)
                max = id;
        }
        return max + 1;
    }

    public void addFriendship(Long user1Id, Long user2Id) {
        User user1 = userRepository.findById(user1Id);
        User user2 = userRepository.findById(user2Id);

        Friendship friendship = new Friendship(
                generateId(),
                user1Id,
                user2Id,
                LocalDateTime.now()
        );

        validator.validate(friendship);

        friendshipRepository.save(friendship);

        user1.addFriend(user2Id);
        user2.addFriend(user1Id);

        userRepository.update(user1);
        userRepository.update(user2);
    }

    public Iterable<Friendship> getAllFriendships() {
        return friendshipRepository.getAll();
    }

    public void deleteFriendship(Long friendshipId) {

        Friendship friendship = friendshipRepository.findById(friendshipId);

        User user1 = userRepository.findById(friendship.getUser1Id());
        User user2 = userRepository.findById(friendship.getUser2Id());

        user1.removeFriend(user2.getId());
        user2.removeFriend(user1.getId());

        userRepository.update(user1);
        userRepository.update(user2);

        friendshipRepository.delete(friendshipId);
    }
}