#include <stdio.h>

union decision {
    unsigned char flags;
    struct field {
        unsigned int your_choice:1; 
        unsigned int your_mothers_choice:1;
        unsigned int your_fathers_choice:1;
        unsigned int socially_acceptable:1;
        unsigned int financially_viable:1;
        unsigned int do_you_aptitude:1;
        unsigned int do_you_likeit:1;
        unsigned int decision:1; 
    } field;
};

// Function to simulate user input
union decision input() {
    union decision d;
    d.flags = 0; // Initialize all bits to 0

    // Simulating inputs: You like it, you have aptitude, but it's not financially viable yet
    d.field.your_mothers_choice = 1;
    d.field.your_fathers_choice = 0;
    d.field.socially_acceptable = 1;
    d.field.financially_viable = 0;
    d.field.do_you_aptitude = 1;
    d.field.do_you_likeit = 1;

    return d;
}

void make_decision(union decision *d) {
    /* 
       Expression: Decision is true if (Aptitude AND Likability) 
       OR if it's socially/financially stable AND parents agree.
    */
    int passion_path = d->field.do_you_aptitude && d->field.do_you_likeit;
    int safe_path = d->field.socially_acceptable && d->field.financially_viable;
    int parental_blessing = d->field.your_mothers_choice || d->field.your_fathers_choice;

    d->field.your_choice = passion_path || (safe_path && parental_blessing);
    
    // The final decision bit is a reflection of your choice
    d->field.decision = d->field.your_choice;
}

void print_decision(union decision d) {
    printf("\n--- Decision Analysis ---\n");
    printf("Aptitude: %s | Passion: %s\n", 
            d.field.do_you_aptitude ? "YES" : "NO", 
            d.field.do_you_likeit ? "YES" : "NO");
    
    if (d.field.decision) {
        printf("Verdict: [PROCEED] The alignment of factors justifies the risk.\n");
    } else {
        printf("Verdict: [HALT] Insufficient conviction or stability.\n");
    }
}

void print_conclusion_based_on_flags(union decision d) {
    printf("\n--- Flag Interpretation ---\n");
    printf("Raw Byte Value (Flags): %u\n", d.flags);

    /* 
       Interesting use: Treat the flag value as 'Entropy'. 
       More bits set = More external/internal factors to weigh.
    */
    if (d.flags > 128) {
        printf("Analysis: High Complexity. Your decision is heavily burdened by external variables.\n");
    } else if (d.flags > 0) {
        printf("Analysis: Lean Logic. You are operating on a focused set of criteria.\n");
    } else {
        printf("Analysis: The Void. No data points provided.\n");
    }
}

int main() {
    union decision my_life = input();
    
    make_decision(&my_life);
    print_decision(my_life);
    print_conclusion_based_on_flags(my_life);

    return 0;
}