# OurShell — Mini interpréteur de commandes UNIX

> **Projet académique** : création d’un mini shell en C sous UNIX (interactive + batch) avec historique simple.

## ✨ Fonctionnalités
- **Mode interactif** : invite `[~$PWD] %` → lit une commande et l’exécute via `fork` + `exec*`.  
- **Historique** : affiche les **10** dernières commandes (`history`).  
- **Mode batch** : si un **fichier** est passé en argument (`argc == 2`), exécute chaque ligne séquentiellement.  
- **Gestion des erreurs** : messages d’erreurs simples en cas d’échec d’exécution.

## 📁 Contenu
- `shell.c` — code source C du shell.
- `docs/choices_of_data_structures_and_algorithms.pdf` — rapport décrivant les choix d’algorithmes et de structures de données.
- `LICENSE` — licence MIT.
- `.gitignore` — ignore les fichiers de build/obj.

## 🛠️ Compilation
```bash
gcc shell.c -o ourshell
```

## ▶️ Utilisation
### Mode interactif
```bash
./ourshell
# tapez des commandes, ex. :
ls -la
history     # affiche les 10 dernières commandes
quit        # quitte le shell
```

### Mode batch (script)
```bash
./ourshell commands.txt
```

## 🧠 Détails d’implémentation (aperçu)
- Boucle principale avec affichage de l’invite, lecture de la ligne, et exécution via `fork()`/`execl`/`execvp` + `waitpid()`.
- Commande builtin `quit` (sortie propre).  
- Commande spéciale `history` (stockage circulaire de 10 entrées).  
- En mode batch : ouverture de fichier, lecture ligne par ligne, `splitLine()` puis exécution.

Pour plus de précisions, voir le rapport PDF dans `docs/`.

## 📦 Roadmap (idées)
- Support des redirections (`>`, `<`) et des pipes (`|`) de façon robuste.
- Complétion & édition de ligne (GNU Readline).
- Persistance de l’historique entre sessions (~/.ourshell_history).
- Tests automatiques (bats/CTest) + CI GitHub Actions.

## 👩‍💻 Auteurs
Projet réalisé dans le cadre académique (voir rapport PDF).

---

> Ce dépôt a vocation pédagogique. Toute contribution d’amélioration est la bienvenue !

