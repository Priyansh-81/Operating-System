#include <stdio.h>
#include <stdlib.h>

int search(int page, int *frame, int frames) {
    for (int i = 0; i < frames; i++)
        if (frame[i] == page) return 1;
    return 0;
}

int predict(int *pages, int *frame, int pagesCount, int index, int frames) {
    int res = -1, farthest = index;
    for (int i = 0; i < frames; i++) {
        int j;
        for (j = index; j < pagesCount; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == pagesCount) return i;
    }
    return (res == -1) ? 0 : res;
}

int main() {
    int pagesCount, frames;
    printf("Enter number of frames: ");
    scanf("%d", &frames);
    printf("Enter number of pages: ");
    scanf("%d", &pagesCount);

    int *pages = (int *)malloc(pagesCount * sizeof(int));
    int *frame = (int *)malloc(frames * sizeof(int));

    printf("Enter the page numbers: ");
    for (int i = 0; i < pagesCount; i++)
        scanf("%d", &pages[i]);

    for (int i = 0; i < frames; i++)
        frame[i] = -1;

    int pageFaults = 0, filled = 0;
    for (int i = 0; i < pagesCount; i++) {
        if (search(pages[i], frame, frames))
            continue;

        if (filled < frames) {
            frame[filled++] = pages[i];
        } else {
            int pos = predict(pages, frame, pagesCount, i + 1, frames);
            frame[pos] = pages[i];
        }
        pageFaults++;
    }

    printf("Total Page Faults = %d\n", pageFaults);
    free(pages);
    free(frame);
    return 0;
}