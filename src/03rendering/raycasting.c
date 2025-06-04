#include"cub3d.h"

/*
Horizontal intersection
ys = cellsize
tan(a) = ys/ xs ->  xs = ys/tan(a)

yn = Player.y - (((int)Player.y/cellsize) *cellsize)

tan(a) = yn/xn -> xn = yn/tan(a)

Vertical interesetion

xs = cellsize
tan(a) = ys/ xs ->  ys = xs/tan(a)

xn = cellsize - player.x + (player.x / cellsize) * cellsize

tan(a) = yn/xn -> xn = yn/tan(a)

RENDERING

h/2 = tan(1/2 a) * d

line ratio = (1/2h)/(h/2)

half line size =  (screen * width)/2 * line ratio



FOV = screen width * step

REMOVING DISTORTION(fish eye)

Vc = Vd * cos(a)

*/
/*#include <stdio.h>
#include <math.h>
#include <stdbool.h>

// ============================================================================
// STRUTTURE DATI FONDAMENTALI
// ============================================================================

// Vettore 2D con coordinate float - equivale a olc::vf2d
typedef struct {
    float x, y;
} Vector2f;

// Vettore 2D con coordinate intere - equivale a olc::vi2d  
typedef struct {
    int x, y;
} Vector2i;

// Struttura per contenere i risultati del raycasting
typedef struct {
    bool hit_found;           // Se abbiamo trovato un muro
    float distance;           // Distanza dal punto di partenza al muro
    Vector2f intersection;    // Punto esatto dell'intersezione
    Vector2i map_cell;       // Coordinate della cella che contiene il muro
    int wall_type;           // Tipo di muro colpito (per texture diverse)
} RaycastResult;

// Struttura per rappresentare la mappa del gioco
typedef struct {
    int* data;              // Array 1D che rappresenta la mappa 2D
    Vector2i size;          // Dimensioni della mappa (larghezza x altezza)
} GameMap;

// ============================================================================
// FUNZIONI MATEMATICHE PER I VETTORI
// ============================================================================

// Crea un nuovo vettore 2D float
Vector2f make_vector2f(float x, float y) {
    Vector2f v = {x, y};
    return v;
}

// Crea un nuovo vettore 2D intero
Vector2i make_vector2i(int x, int y) {
    Vector2i v = {x, y};
    return v;
}

// Calcola la lunghezza (magnitudine) di un vettore
float vector2f_length(Vector2f v) {
    return sqrtf(v.x * v.x + v.y * v.y);
}

// Normalizza un vettore (lo rende di lunghezza 1 mantenendo la direzione)
Vector2f vector2f_normalize(Vector2f v) {
    float len = vector2f_length(v);
    if (len > 0.0f) {
        return make_vector2f(v.x / len, v.y / len);
    }
    return make_vector2f(0.0f, 0.0f); // Vettore nullo se lunghezza è zero
}

// Sottrazione tra vettori (v1 - v2)
Vector2f vector2f_subtract(Vector2f v1, Vector2f v2) {
    return make_vector2f(v1.x - v2.x, v1.y - v2.y);
}

// Moltiplicazione di un vettore per uno scalare
Vector2f vector2f_multiply(Vector2f v, float scalar) {
    return make_vector2f(v.x * scalar, v.y * scalar);
}

// Addizione tra vettori (v1 + v2)
Vector2f vector2f_add(Vector2f v1, Vector2f v2) {
    return make_vector2f(v1.x + v2.x, v1.y + v2.y);
}

// Converte un vettore float in un vettore intero (tronca i decimali)
Vector2i vector2f_to_vector2i(Vector2f v) {
    return make_vector2i((int)v.x, (int)v.y);
}

// ============================================================================
// FUNZIONI PER LA GESTIONE DELLA MAPPA
// ============================================================================

// Crea una nuova mappa con le dimensioni specificate
GameMap* create_map(int width, int height) {
    GameMap* map = (GameMap*)malloc(sizeof(GameMap));
    if (!map) return NULL;
    
    map->size = make_vector2i(width, height);
    map->data = (int*)calloc(width * height, sizeof(int));
    
    if (!map->data) {
        free(map);
        return NULL;
    }
    
    return map;
}

// Libera la memoria occupata dalla mappa
void destroy_map(GameMap* map) {
    if (map) {
        if (map->data) free(map->data);
        free(map);
    }
}

// Ottiene il valore di una cella della mappa (con controllo dei limiti)
int get_map_cell(GameMap* map, int x, int y) {
    if (!map || !map->data) return 1; // Considera come muro se mappa non valida
    if (x < 0 || x >= map->size.x || y < 0 || y >= map->size.y) {
        return 1; // Fuori dai limiti = muro
    }
    return map->data[y * map->size.x + x];
}

// Imposta il valore di una cella della mappa
void set_map_cell(GameMap* map, int x, int y, int value) {
    if (!map || !map->data) return;
    if (x < 0 || x >= map->size.x || y < 0 || y >= map->size.y) return;
    map->data[y * map->size.x + x] = value;
}

// ============================================================================
// ALGORITMO DDA PER IL RAYCASTING
// ============================================================================

RaycastResult raycast_dda(Vector2f ray_start, Vector2f ray_direction, GameMap* map, float max_distance) {
    RaycastResult result = {0}; // Inizializza tutto a zero/false
    
    // Normalizza la direzione del raggio per sicurezza
    ray_direction = vector2f_normalize(ray_direction);
    
    // Se la direzione è nulla, non possiamo proseguire
    if (ray_direction.x == 0.0f && ray_direction.y == 0.0f) {
        return result;
    }
    
    // ========================================================================
    // FASE 1: CALCOLO DELLE LUNGHEZZE UNITARIE
    // ========================================================================
    
    // Questo è il cuore matematico del DDA. Calcoliamo quanto dobbiamo
    // viaggiare lungo il raggio per spostarci di una unità nella griglia.
    // La formula sqrt(1 + (dy/dx)²) deriva dal teorema di Pitagora.
    Vector2f ray_unit_step_size;
    
    // Per evitare divisioni per zero, usiamo un valore molto piccolo invece di zero
    float safe_ray_dir_x = (ray_direction.x == 0.0f) ? 1e-30f : ray_direction.x;
    float safe_ray_dir_y = (ray_direction.y == 0.0f) ? 1e-30f : ray_direction.y;
    
    ray_unit_step_size.x = sqrtf(1.0f + (ray_direction.y / safe_ray_dir_x) * (ray_direction.y / safe_ray_dir_x));
    ray_unit_step_size.y = sqrtf(1.0f + (ray_direction.x / safe_ray_dir_y) * (ray_direction.x / safe_ray_dir_y));
    
    // ========================================================================
    // FASE 2: IMPOSTAZIONE DELLE CONDIZIONI INIZIALI
    // ========================================================================
    
    // Determiniamo la cella della griglia in cui iniziamo
    Vector2i map_check = vector2f_to_vector2i(ray_start);
    
    // Queste variabili tengono traccia di quanto dobbiamo viaggiare per
    // raggiungere la prossima linea della griglia in ogni direzione
    Vector2f ray_length_1d;
    
    // La direzione in cui ci muoviamo nella griglia (-1 o +1 per ogni asse)
    Vector2i step;
    
    // Calcoliamo la direzione del passo e la distanza iniziale per l'asse X
    if (ray_direction.x < 0) {
        step.x = -1;
        // Se andiamo verso sinistra, calcoliamo la distanza al bordo sinistro della cella
        ray_length_1d.x = (ray_start.x - (float)map_check.x) * ray_unit_step_size.x;
    } else {
        step.x = 1;
        // Se andiamo verso destra, calcoliamo la distanza al bordo destro della cella
        ray_length_1d.x = ((float)(map_check.x + 1) - ray_start.x) * ray_unit_step_size.x;
    }
    
    // Stessa logica per l'asse Y
    if (ray_direction.y < 0) {
        step.y = -1;
        ray_length_1d.y = (ray_start.y - (float)map_check.y) * ray_unit_step_size.y;
    } else {
        step.y = 1;
        ray_length_1d.y = ((float)(map_check.y + 1) - ray_start.y) * ray_unit_step_size.y;
    }
    
    // ========================================================================
    // FASE 3: ESECUZIONE DEL DDA - IL LOOP PRINCIPALE
    // ========================================================================
    
    bool tile_found = false;
    float distance = 0.0f;
    
    // Continuiamo a "camminare" lungo il raggio fino a trovare un muro
    // o fino a superare la distanza massima
    while (!tile_found && distance < max_distance) {
        // Scegliamo se muoverci lungo l'asse X o Y basandoci su quale
        // linea della griglia è più vicina
        if (ray_length_1d.x < ray_length_1d.y) {
            // Il prossimo incrocio è su una linea verticale
            map_check.x += step.x;
            distance = ray_length_1d.x;
            ray_length_1d.x += ray_unit_step_size.x;
        } else {
            // Il prossimo incrocio è su una linea orizzontale
            map_check.y += step.y;
            distance = ray_length_1d.y;
            ray_length_1d.y += ray_unit_step_size.y;
        }
        
        // Controlliamo se la nuova posizione contiene un muro
        int cell_value = get_map_cell(map, map_check.x, map_check.y);
        if (cell_value != 0) {
            tile_found = true;
            result.hit_found = true;
            result.distance = distance;
            result.map_cell = map_check;
            result.wall_type = cell_value;
            
            // Calcoliamo il punto esatto dell'intersezione
            result.intersection = vector2f_add(ray_start, vector2f_multiply(ray_direction, distance));
        }
    }
    
    return result;
}

// ============================================================================
// FUNZIONI DI ESEMPIO E TEST
// ============================================================================

// Crea una mappa di esempio per testare il raycasting
GameMap* create_example_map() {
    GameMap* map = create_map(10, 10);
    if (!map) return NULL;
    
    // Creiamo una stanza con muri perimetrali e alcuni ostacoli interni
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            if (x == 0 || x == 9 || y == 0 || y == 9) {
                set_map_cell(map, x, y, 1); // Muri perimetrali
            } else if ((x == 3 && y >= 2 && y <= 5) || (x == 7 && y >= 4 && y <= 7)) {
                set_map_cell(map, x, y, 2); // Pilastri interni
            } else {
                set_map_cell(map, x, y, 0); // Spazio vuoto
            }
        }
    }
    
    return map;
}

// Stampa la mappa per debug
void print_map(GameMap* map) {
    if (!map) return;
    
    printf("Mappa %dx%d:\n", map->size.x, map->size.y);
    for (int y = 0; y < map->size.y; y++) {
        for (int x = 0; x < map->size.x; x++) {
            int cell = get_map_cell(map, x, y);
            printf("%c", (cell == 0) ? '.' : '0' + cell);
        }
        printf("\n");
    }
    printf("\n");
}

// Funzione di test per dimostrare l'uso del raycasting
void test_raycast_engine() {
    printf("=== TEST DEL MOTORE DI RAYCASTING DDA ===\n\n");
    
    // Creiamo una mappa di esempio
    GameMap* map = create_example_map();
    if (!map) {
        printf("Errore: impossibile creare la mappa!\n");
        return;
    }
    
    print_map(map);
    
    // Testiamo diversi raggi dalla posizione del giocatore
    Vector2f player_pos = make_vector2f(5.5f, 5.5f);
    
    printf("Posizione giocatore: (%.1f, %.1f)\n\n", player_pos.x, player_pos.y);
    
    // Test di raggi in diverse direzioni
    Vector2f directions[] = {
        make_vector2f(1.0f, 0.0f),    // Est
        make_vector2f(0.0f, 1.0f),    // Sud  
        make_vector2f(-1.0f, 0.0f),   // Ovest
        make_vector2f(0.0f, -1.0f),   // Nord
        make_vector2f(1.0f, 1.0f),    // Sud-Est
        make_vector2f(-1.0f, -1.0f),  // Nord-Ovest
    };
    
    const char* direction_names[] = {
        "Est", "Sud", "Ovest", "Nord", "Sud-Est", "Nord-Ovest"
    };
    
    for (int i = 0; i < 6; i++) {
        RaycastResult result = raycast_dda(player_pos, directions[i], map, 20.0f);
        
        printf("Raggio verso %s:\n", direction_names[i]);
        if (result.hit_found) {
            printf("  - Muro trovato alla distanza: %.2f\n", result.distance);
            printf("  - Posizione: cella (%d, %d)\n", result.map_cell.x, result.map_cell.y);
            printf("  - Intersezione: (%.2f, %.2f)\n", result.intersection.x, result.intersection.y);
            printf("  - Tipo muro: %d\n", result.wall_type);
        } else {
            printf("  - Nessun muro trovato entro la distanza massima\n");
        }
        printf("\n");
    }
    
    // Liberiamo la memoria
    destroy_map(map);
}

int main() {
    test_raycast_engine();
    return 0;
}*/
