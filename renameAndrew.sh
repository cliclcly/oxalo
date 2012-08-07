git filter-branch --env-filter '
      if [ "$GIT_COMMITTER_NAME" = "unknown" ];
      then
          export GIT_AUTHOR_EMAIL="mdandrewm@gmail.com";
          export GIT_AUTHOR_NAME="Andrew McCurry";
          export GIT_COMMITTER_EMAIL="mdandrewm@gmail.com";
          export GIT_COMMITTER_NAME="Andrew McCurry";
      fi' HEAD