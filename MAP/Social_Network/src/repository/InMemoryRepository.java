package repository;

import Domain.Entity;
import validator.RepositoryException;

import java.util.HashMap;
import java.util.Map;


public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID,E> {

    protected Map<ID,E> entities = new HashMap<>();


    @Override
    public E findById(ID id) {

        E entity = entities.get(id);

        if (entity == null) {
            throw new RepositoryException("Entity not found");
        }
        return entity;
    }

    @Override
    public Iterable<E> getAll() {
        return entities.values();
    }

    @Override
    public void save(E entity) {

        if (entities.containsKey(entity.getId())) {
            throw new RepositoryException("id already exists");
        }
        entities.put(entity.getId(), entity);
    }

    @Override
    public void delete(ID id) {

        if (!entities.containsKey(id)) {
            throw new RepositoryException("Entity not found");
        }
        entities.remove(id);
    }

    @Override
    public void update(E entity) {

        if (!entities.containsKey(entity.getId())) {
            throw new RepositoryException("Entity not found");
        }
        entities.put(entity.getId(), entity);
    }

    @Override
    public Iterable<ID> getKeys() {
        return entities.keySet();
    }

    public boolean isEmpty(){
        return entities.isEmpty();
    }



}
