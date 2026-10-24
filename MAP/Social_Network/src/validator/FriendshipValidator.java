package validator;

import Domain.Friendship;

public class FriendshipValidator implements Validator<Friendship> {

    @Override
    public void validate(Friendship friendship) {

        if (friendship == null)
            throw new ValidationException("Friendship cannot be null");

        if (friendship.getId() == null)
            throw new ValidationException("ID cannot be null");

        if (friendship.getUser1Id() == null ||
                friendship.getUser2Id() == null)
            throw new ValidationException("User IDs cannot be null");

        if (friendship.getUser1Id().equals(friendship.getUser2Id()))
            throw new ValidationException("A user cannot be friend with himself");
    }
}