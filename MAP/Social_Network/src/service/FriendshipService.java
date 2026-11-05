package service;

import Domain.Friendship;
import Domain.User;
import repository.Repository;
import validator.FriendshipValidator;
import validator.Validator;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class FriendshipService {

    private Repository<Long, Friendship> friendshipRepository;
    private Repository<Long, User> userRepository;
    private FriendshipValidator validator;
    private Long nextId;

    public FriendshipService(
            Repository<Long, Friendship> friendshipRepository,
            Repository<Long, User> userRepository,
            Validator<Friendship> validator) {

        this.friendshipRepository = friendshipRepository;
        this.userRepository = userRepository;
        this.validator = (FriendshipValidator) validator;
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
        for (Friendship existing : friendshipRepository.getAll()) {
            boolean samePair =
                    (existing.getUser1Id().equals(user1Id) && existing.getUser2Id().equals(user2Id)) ||
                            (existing.getUser1Id().equals(user2Id) && existing.getUser2Id().equals(user1Id));

            if (samePair) {
                throw new IllegalArgumentException("These users are already friends");
            }
        }
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

    public void deleteFriendshipsForUser(Long userId) {
        List<Long> idsToDelete = new ArrayList<>();

        for (Friendship friendship : friendshipRepository.getAll()) {
            if (friendship.getUser1Id().equals(userId) ||
                    friendship.getUser2Id().equals(userId)) {
                idsToDelete.add(friendship.getId());
            }
        }

        for (Long id : idsToDelete) {
            deleteFriendship(id);
        }
    }
}