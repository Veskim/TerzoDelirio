public class Song {
    String artist;
    String title;
    static int Max_Lenght= 3600;
    String musicPlatform;
    int playSecond;


    Song(String artist, String title, String platform){

        if(artist == null || title == null)
            System.out.err("Errore! mancano artista/titolo")    
        else {
            this.artist = artist;
            this.title = title;
            this.musicPlatform = platform;
            this.playSecond = 0;
        }
    }
    
    int getPlayCount(){
        returno 0;
    }

    void resetPlayCount(){

    }

    void f(){
        String artist = "Muse";
        this.artist = artist;
    }
}

