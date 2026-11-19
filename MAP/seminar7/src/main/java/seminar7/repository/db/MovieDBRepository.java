package seminar7.repository.db;

import seminar7.domain.Movie;
import seminar7.domain.validators.Validator;
import seminar7.repository.Repository;
import seminar7.repository.RepositoryException;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class MovieDBRepository implements Repository<Long,Movie> {
    private final Validator<Movie> validator;
    private final String url;
    private final String username;
    private final String password;

    public MovieDBRepository(Validator<Movie> validator, String url, String username, String password) {
        this.validator = validator;
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public Optional<Movie> findOne(Long id) {
        return Optional.empty();
    }

    @Override
    public Iterable<Movie> findAll() {

        List<Movie> movies = new ArrayList<>();

        try(Connection connection = DriverManager.getConnection(url, username, password);
            PreparedStatement ps = connection.prepareStatement("select * from filme order by id");
            ResultSet rs = ps.executeQuery()
            )
        {
            while(rs.next()){
                Movie m = new Movie(rs.getString("titlu"),
                        rs.getString("regizor"),
                        rs.getInt("an"),
                        rs.getInt("durata"));
                m.setId(rs.getLong("id"));
                movies.add(m);
            }
        }catch (SQLException e){
            throw new RepositoryException("error db" + e.getMessage(), e);
        }
        return null;
    }

    @Override
    public Optional<Movie> save(Movie entity) {

        if(entity == null){
            throw new IllegalArgumentException("sdfdsf");
        }

        validator.validate(entity);
        String sql = "insert into filme(titlu, regizor, an, durata) values(?,?,?,?)";
        try(Connection connection = DriverManager.getConnection(url, username, password);
        PreparedStatement ps = connection.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)){
            ps.setString(1, entity.getTitle());
            ps.setString(2, entity.getDirector());
            ps.setInt(3, entity.getYear());
            ps.setInt(4, entity.getDuration());
            ps.executeUpdate();
            try(ResultSet rs = ps.getGeneratedKeys()){
                rs.next();
                entity.setId(rs.getLong("id"));
            }

        }catch(SQLException e){

        }


        return Optional.empty();
    }

    @Override
    public Optional<Movie> delete(Long id) {
        return Optional.empty();
    }

    @Override
    public Optional<Movie> update(Movie entity) {
        if(entity == null){
            throw new IllegalArgumentException("a");
        }
        validator.validate(entity);
        try(Connection connection = DriverManager.getConnection(url, username, password);
        PreparedStatement ps = connection.prepareStatement("update filme set titlu = ?, regizor = ?" + "an = ?, durata = ?"))
    }


    public List<Movie> findByDirector(String director) {
        List<Movie> movies = new ArrayList<>();
        // TODO: Implement the logic to retrieve movies by director order by year from the database

    try(Connection connection = DriverManager.getConnection(url, username, password);

        PreparedStatement ps = connection.prepareStatement("select * from filme where regizor ")


    ){

    }catch(SQLException e){
        throw new RepositoryException("dad" + e.getMessage(),  e);
    }


        return movies;
    }
}
