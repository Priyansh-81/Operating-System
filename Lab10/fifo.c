#include <stdio.h>
#include <stdlib.h>

int main() {
    int frames, pages, i, j, k, pageFaults = 0, index = 0;
    printf("Enter number of frames: ");
    scanf("%d", &frames);
    printf("Enter number of pages: ");
    scanf("%d", &pages);

    int *page = (int *)malloc(pages * sizeof(int));
    int *frame = (int *)malloc(frames * sizeof(int));

    printf("Enter the page numbers: ");
    for (i = 0; i < pages; i++)
        scanf("%d", &page[i]);

    for (i = 0; i < frames; i++)
        frame[i] = -1;

    for (i = 0; i < pages; i++) {
        int found = 0;
        for (j = 0; j < frames; j++) {
            if (frame[j] == page[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frame[index] = page[i];
            index = (index + 1) % frames;
            pageFaults++;
        }
    }

    printf("Total Page Faults = %d\n", pageFaults);
    free(page);
    free(frame);
    return 0;
}