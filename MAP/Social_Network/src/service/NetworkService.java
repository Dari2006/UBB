package service;

import Domain.Friendship;
import Domain.User;
import repository.FriendshipRepository;
import repository.InMemoryRepository;
import repository.Repository;
import repository.UserRepository;

import java.util.*;

public class NetworkService {
    private Repository<Long, User> userRepository;
    private Repository<Long, Friendship> friendshipRepository;

    public NetworkService(Repository<Long, User> userRepository, Repository<Long, Friendship> friendshipRepository) {
        this.userRepository = userRepository;
        this.friendshipRepository = friendshipRepository;
    }


    private List<User> getNeighbours(User user) {
        List<User> neighbours = new ArrayList<>();

        for (Friendship friendship : friendshipRepository.getAll()) {

            if (friendship.getUser1Id().equals(user.getId())) {
                neighbours.add(
                        userRepository.findById(friendship.getUser2Id())
                );
            }

            if (friendship.getUser2Id().equals(user.getId())) {
                neighbours.add(
                        userRepository.findById(friendship.getUser1Id())
                );
            }
        }

        return neighbours;
    }

    private void dfs(User user, Set<User> visited, List<User> community) {
        visited.add(user);
        community.add(user);

        for (User neighbour : getNeighbours(user)) {
            if (!visited.contains(neighbour)) {
                dfs(neighbour, visited, community);
            }
        }
    }

    public int getNumberOfCommunities() {
        int count = 0;

        Set<User> visited = new HashSet<>();

        for (User user : userRepository.getAll()) {

            if (!visited.contains(user)) {
                count++;
                dfs(user, visited, new ArrayList<>());
            }
        }

        return count;
    }

    private int bfsMaxDistance(User start) {

        Queue<User> queue = new LinkedList<>();
        Map<User,Integer> distance = new HashMap<>();

        queue.add(start);
        distance.put(start,0);

        int max = 0;

        while(!queue.isEmpty()) {

            User current = queue.poll();

            for(User neighbour : getNeighbours(current)) {

                if(!distance.containsKey(neighbour)) {

                    distance.put(
                            neighbour,
                            distance.get(current)+1
                    );

                    max = Math.max(
                            max,
                            distance.get(neighbour)
                    );

                    queue.add(neighbour);
                }
            }
        }

        return max;
    }

    private int getCommunityDiameter(List<User> community) {

        int max = 0;

        for(User user : community) {
            max = Math.max(
                    max,
                    bfsMaxDistance(user)
            );
        }

        return max;
    }

    public List<User> getMostSocialCommunity() {

        Set<User> visited = new HashSet<>();

        List<User> bestCommunity = null;
        int biggestDiameter = -1;


        for(User user : userRepository.getAll()) {

            if(!visited.contains(user)) {

                List<User> community = new ArrayList<>();

                dfs(user, visited, community);


                int diameter = getCommunityDiameter(community);


                if(diameter > biggestDiameter) {
                    biggestDiameter = diameter;
                    bestCommunity = community;
                }
            }
        }

        return bestCommunity;
    }
}
