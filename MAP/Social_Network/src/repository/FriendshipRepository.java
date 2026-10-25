package repository;

import Domain.Friendship;
import validator.Validator;

public class FriendshipRepository extends InMemoryRepository<Long, Friendship> {

    public FriendshipRepository(Validator<Friendship> validator) {
        super(validator);
    }
}