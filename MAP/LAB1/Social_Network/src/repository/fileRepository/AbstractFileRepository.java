package repository.fileRepository;

import Domain.Entity;
import repository.InMemoryRepository;
import repository.Repository;
import validator.RepositoryException;
import validator.Validator;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.function.Function;

import static java.nio.file.Files.newBufferedReader;

public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID, E> {
    private final String filename;

    public AbstractFileRepository(String filename, Validator<E> validator) {
        super(validator);
        this.filename = filename;
        try{
            loadData();
        }
        catch (IOException e){
            throw new RepositoryException("could not load data");
        }
    }

    public AbstractFileRepository(String filename, Validator<E> validator, Function<E, ?> uniqueExtractor) {
        super(validator, uniqueExtractor);
        this.filename = filename;
        try{
            loadData();
        }
        catch (IOException e){
            throw new RepositoryException("could not load data");
        }
    }

    /**
     * abstract method that receives a String line and creates an entity
     * @param line: String, the line that contains entity params
     * @return new entity
     */
    public abstract E  extractEntity(String line);

    /**
     * abstract method that receives an entity and creates a string from its params
     * @param e, the Entity to tunr into a string
     * @return String containing params
     */
    public abstract String parseEntity(E e);

    /**
     * method that loads data from file into memory
     * @throws IOException
     */
    private void loadData() throws IOException {
        Path path = Path.of(filename);

            if(Files.notExists(path)){
                Files.createFile(path);
            }
            try(BufferedReader in = Files.newBufferedReader(path)) {
                String line;
                int currLine = 0;
                while ((line = in.readLine()) != null) {
                    currLine++;
                    try {
                        E e = extractEntity(line);
                        super.save(e);
                    } catch (RepositoryException ex) {
                        System.err.println("error on line: " + currLine);
                    }
                }
            }
    }

    /**
     * method that saves data from memory to a file
     * @throws IOException
     */
    private void saveData() throws IOException {
        Path path = Path.of(filename);
        if(Files.notExists(path)){
            Files.createFile(path);
        }
        Iterable<E> all = super.getAll();
        try(BufferedWriter out = Files.newBufferedWriter(path)){
            for(E e : all){
                out.write(parseEntity(e));
                out.newLine();
            }
        }
    }

    @Override
    public void save(E entity) {
        try{
            super.save(entity);
            saveData();
        }
        catch(IOException e){
            throw new RepositoryException("could not save");
        }
    }

    @Override
    public void delete(ID id) {

        super.delete(id);
        try {
            saveData();
        } catch (IOException e) {
            throw new RepositoryException("could not save");
        }
    }

    @Override
    public void update(E entity) {
        super.update(entity);
        try {
            saveData();
        } catch (IOException e) {
            throw new RepositoryException("could not save");
        }
    }
}
