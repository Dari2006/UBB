package repository;

import Domain.Entity;
import validator.RepositoryException;
import validator.Validator;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.function.Function;


public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID,E> {

    protected Map<ID,E> entities = new HashMap<>();
    Validator<E> validator;

    protected Function<E, ?> uniqueExtractor;
    protected Set<Object> uniqueValues;

    public InMemoryRepository(Validator<E> validator) {
        this.validator = validator;
        this.uniqueExtractor = null;
        this.uniqueValues = null;
    }

    public InMemoryRepository(Validator<E> validator, Function<E, ?> uniqueExtractor) {
        this.validator = validator;
        this.uniqueExtractor = uniqueExtractor;
        this.uniqueValues = new HashSet<>();
    }

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

        if(uniqueExtractor != null){
            Object value = uniqueExtractor.apply(entity);
            if(uniqueValues.contains(value)){
                throw new RepositoryException("unique identifier already exists");
            }
            uniqueValues.add(value);
        }

        entities.put(entity.getId(), entity);
    }

    @Override
    public void delete(ID id) {

        if (!entities.containsKey(id)) {
            throw new RepositoryException("Entity not found");
        }
        if(uniqueExtractor != null){
            E e = findById(id);
            Object value = uniqueExtractor.apply(e);
            uniqueValues.remove(value);
        }
        entities.remove(id);
    }

    @Override
    public void update(E entity) {

        if (!entities.containsKey(entity.getId())) {
            throw new RepositoryException("Entity not found");
        }
        if(uniqueExtractor != null){
            ID id = entity.getId();
            E oldEntity = findById(id);
            Object oldValue = uniqueExtractor.apply(oldEntity);
            Object newValue = uniqueExtractor.apply(entity);
            uniqueValues.remove(oldValue);
            uniqueValues.add(newValue);
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
