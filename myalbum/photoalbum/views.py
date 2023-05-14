from django.shortcuts import render, get_object_or_404, redirect
from .models import Album, Photo
from .forms import PhotoForm

def album_list(request):
    albums = Album.objects.all()
    return render(request, 'photoalbum/album_list.html', {'albums': albums})

def album_detail(request, pk):
    album = get_object_or_404(Album, pk=pk)
    photos = album.photo_set.all()
    return render(request, 'photoalbum/album_detail.html', {'album': album, 'photos': photos})

def photo_upload(request):
    if request.method == 'POST':
        form = PhotoForm(request.POST, request.FILES)
        if form.is_valid():
            form.save()
            return redirect('album_list')
    else:
        form = PhotoForm()
    return render(request, 'photoalbum/photo_upload.html', {'form': form})
