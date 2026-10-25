package repository.fileRepository;

import Domain.Entity;
import repository.InMemoryRepository;
import validator.RepositoryException;
import validator.Validator;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;

import static java.nio.file.Files.newBufferedReader;

public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID, E> {
    private final String filename;

    public AbstractFileRepository(String filename, Validator<E> validator){
        super(validator);
        this.filename = filename;
        loadData();
    }


    public abstract E  extractEntity(String line);
    public abstract String parseEntity(E e);


    public void loadData(){
        Path path = Path.of(filename);

        try{
            if(Files.notExists(path)){
                Files.createFile(path);
            }
            try(BufferedReader in = Files.newBufferedReader(path)){
                String line;
                while((line = in.readLine()) != null){
                    E e = extractEntity(line);
                    super.save(e);
                }
            }
        }
        catch(IOException e){
            throw new RepositoryException("file error");

        }
    }

    public void saveData(){
        Path path = Path.of(filename);
        Iterable<E> all = super.getAll();
        try(BufferedWriter out = Files.newBufferedWriter(path)){
            for(E e : all){
                out.write(parseEntity(e));
                out.newLine();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void save(E entity) {
        super.save(entity);
        saveData();
    }

    @Override
    public void delete(ID id) {
        super.delete(id);
        saveData();
    }

    @Override
    public void update(E entity) {
        super.update(entity);
        saveData();
    }
}
