#include <stdio.h>
#include <stdlib.h>

int findLRU(int *time, int n) {
    int i, minimum = time[0], pos = 0;
    for (i = 1; i < n; ++i) {
        if (time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int frames, pages, pageFaults = 0;
    printf("Enter number of frames: ");
    scanf("%d", &frames);
    printf("Enter number of pages: ");
    scanf("%d", &pages);

    int *page = (int *)malloc(pages * sizeof(int));
    int *frame = (int *)malloc(frames * sizeof(int));
    int *time = (int *)malloc(frames * sizeof(int));

    printf("Enter the page numbers: ");
    for (int i = 0; i < pages; i++)
        scanf("%d", &page[i]);

    for (int i = 0; i < frames; i++)
        frame[i] = -1;

    int counter = 0;
    for (int i = 0; i < pages; ++i) {
        int flag = 0;
        for (int j = 0; j < frames; ++j) {
            if (frame[j] == page[i]) {
                counter++;
                time[j] = counter;
                flag = 1;
                break;
            }
        }

        if (!flag) {
            int pos = -1;
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }
            if (pos == -1) {
                pos = findLRU(time, frames);
            }

            frame[pos] = page[i];
            counter++;
            time[pos] = counter;
            pageFaults++;
        }
    }

    printf("Total Page Faults = %d\n", pageFaults);
    free(page);
    free(frame);
    free(time);
    return 0;
}