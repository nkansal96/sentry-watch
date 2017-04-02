window.onscroll = function() {
    var pos = document.body.scrollTop;
    document.getElementById('concept-tab').classList.remove('navitem-selected');
    document.getElementById('features-tab').classList.remove('navitem-selected');
    document.getElementById('team-tab').classList.remove('navitem-selected');

    if (pos >= document.getElementById('team').offsetTop)
        document.getElementById('team-tab').classList.add('navitem-selected');
    else if (pos >= document.getElementById('features').offsetTop)
        document.getElementById('features-tab').classList.add('navitem-selected');
    else if (pos >= document.getElementById('concept').offsetTop)
        document.getElementById('concept-tab').classList.add('navitem-selected');
};
